/** @author James W. Barnett */

#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <iomanip>
using namespace std;

// Reference:
// http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p) 
{
    return std::pair<B,A>(p.second, p.first);
}

// Reference:
// http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src) 
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

map <string, double> bootstrap_uncertainty(int NTEAMS, int bootstrap_n, int NRAND, vector <string> &teams,vector < map <string, double> > &ranks_all);
void output(multimap<double,string> &avgRankSorted, map <string, double> &uncertainty, string outfile, string plotfile);

int main(int argc, char *argv[]) 
{

	 /* 
	  * higher means less movementFactor per win/loss, lower means more
	  * movementFactor less than 2.0 means the two teams will pass each other
	  * movementFactor less than 1.0 means the two teams completely swap (too much
	  * incentive for teams that lose alot to have a couple of wins and be
	  * highly ranked).
	  */
	const int bootstrap_n = 50;
	const double movementFactor = 4.0;
	const int maxOffset = 25;
	int NRAND;
	bool alreadyDone;
	bool winnerIsFBS;
	bool loserIsFBS;
	double offset;
	double score;
	ifstream iFS;
	int i;
	int j;
	int k;
	int loserRank;
	int newLoserRank;
	int newWinnerRank;
	int winnerRank;
	map <string, double> avgRank;
	map <string, double> uncertainty;
	multimap<double,string> avgRankSorted;
	ofstream oFS;
	string configfile;
	string team;
	string winner;
	string loser;
	string space;
	string winslossfile;
	string outfile;
	string plotfile;
	string teamsfile;
	string tmpLoser;
	string tmpWinner;
	string tmp;
	vector <string> teams;
	vector <string> winners;
	vector <string> losers;
	vector <string> nonFBSteams;

	if (argc != 2) 
	{
		cout << "First argument must be configuration file." << endl;
		return -1;
	}

	configfile = argv[1];
	
	srand(time(NULL));

	iFS.open(configfile.c_str());
	iFS >> NRAND;
	iFS >> teamsfile;
	iFS >> winslossfile;
	iFS >> outfile;
	iFS >> plotfile;
	iFS.close();

	cout << "Random permutations to perform: " << NRAND << endl;
	cout << "Reading teams from: " << teamsfile << endl;
	cout << "Reading records from: " << winslossfile << endl;
	cout << "Ranking will be output to: " << outfile << endl;
	cout << "Plot file is: " << plotfile << endl;

	vector < map <string, double> > ranks_all(NRAND);

	iFS.open(teamsfile.c_str());

	// Read in the FBS teams from a file
	while(getline(iFS,team)) 
	{
		teams.push_back(team);
		avgRank[team] = 0.0;
		for (i = 0; i < NRAND; i++)
		{
			ranks_all.at(i)[team] = 0.0;
		}
	}

	iFS.close();

	const int NTEAMS = teams.size();
	cout << "Number of teams: " << NTEAMS << endl;

	/* Read in and store win-loss records. */
	iFS.open(winslossfile.c_str());
	while (!iFS.eof()) 
	{

		/* Read in this record. Record is always winner first, then loser,
		* then a blank line. */
		getline(iFS,winner);
		getline(iFS,loser);
		getline(iFS,space);
		if (iFS.eof()) 
		{	
			break;
		}
		winners.push_back(winner);
		losers.push_back(loser);

		/* Check if winner and loser are FBS teams or not */
		winnerIsFBS = false;
		for (i = 0; i < NTEAMS; i++)
		{
			if (winner == teams.at(i))
			{
				winnerIsFBS = true;
				break;
			}
		}
		if (!winnerIsFBS)
		{
			alreadyDone = false;
			for (i = 0; i < nonFBSteams.size(); i++)
			{
				if (winner == nonFBSteams.at(i))
				{
					alreadyDone = true;
					break;
				}
			}

			if (!alreadyDone)
			{
				nonFBSteams.push_back(winner);
			}
		}
		loserIsFBS= false;
		for (i = 0; i < NTEAMS; i++)
		{
			if (loser == teams.at(i))
			{
				loserIsFBS = true;
				break;
			}
		}
		if (!loserIsFBS)
		{
			alreadyDone = false;
			for (i = 0; i < nonFBSteams.size(); i++)
			{
				if (loser == nonFBSteams.at(i))
				{
					alreadyDone = true;
					break;
				}
			}

			if (!alreadyDone)
			{
				nonFBSteams.push_back(loser);
			}
		}
	}

	iFS.close();


	const int NRECORDS = winners.size();
	cout << "Number of games: " << NRECORDS << endl;

	const int NNONFBS = nonFBSteams.size();
	oFS.open("nonFBS.txt");
	oFS << "The following have been determined to be non-FBS teams. CHECK FOR ACCURACY: " << endl;
	for (i = 0; i < NNONFBS; i++)
	{
		oFS << nonFBSteams.at(i) << endl;
	}
	oFS.close();

	for (i = 0; i < NRAND; i++) 
	{

		cout << "Iteration: " << i << endl;

		random_shuffle(teams.begin(), teams.end());

		for (int record = 0; record < NRECORDS; record++)
		{

			/* Find out the rank of the winner and loser in this random
			 * permutation. Also find out if the winner and loser are both FBS
			 * teams. */
			winnerIsFBS = false;
			loserIsFBS = false;
			for (j = 0; j < NTEAMS; j++) 
			{

				if (teams.at(j) == winners.at(record)) 
				{
					winnerRank = j; 
					winnerIsFBS = true;
				}
				if (teams.at(j) == losers.at(record)) 
				{
					loserRank = j;
					loserIsFBS = true;
				}

				if (loserIsFBS && winnerIsFBS) 
				{ 
					break;
				}

			}

			/* 
			 * If both teams are FBS and the loser is more highly ranked than
			 * the winner, the loser moves down and the winner moves up. You
			 * can only move up or down the maximum offset. You can't move
			 * up higher than number 1, and you can't be lower than the number of
			 * teams. If the team you beat is just above you, you switch spots.
			 * If you play an FCS team and lose you go to the bottom. After all
			 * of that, shift the other teams around the movement. It's a little
			 * counterintuitive here - ranks that are numerically lower are
			 * better ranks, and ranks that are numerically higher, are worse
			 * ranks.
			 */
			if (winnerIsFBS && loserIsFBS && winnerRank > loserRank) 
			{
				// Determine the offset that will be used to move the teams
				offset = (winnerRank - loserRank) / movementFactor;

				// Can only move so far
				if (offset > maxOffset)
				{	
					offset = maxOffset;
				}

				// Initial shift
				newLoserRank = (loserRank + offset);
				newWinnerRank = (winnerRank - offset);

				// If the winner is ranked higher than the number one spot, then
				// move it down to number one.
				if (newWinnerRank < 0) 
				{ 
					newWinnerRank = 0;
				}
				
				// If the loser is ranked lower than the possible number of
				// teams, move it up to last place.
				if (newLoserRank > NTEAMS-1) 
				{ 
					newLoserRank = NTEAMS-1;
				}

				// If somehow they are ranked the same, the loser moves down one
				// spot
				if (newWinnerRank == newLoserRank) 
				{ 
					newWinnerRank = newLoserRank + 1;
				}

				// Now move the other teams around. Because the new winner moved
				// up, the teams that are no below it have to move down in rank
				// by 1.
				for (k = winnerRank-1; k >= newWinnerRank; k--) 
				{
					teams.at(k+1) = teams.at(k);
				}

				// Because the new loser moved down in rank, the teams around it
				// have to move up in rank by 1.
				for (k = loserRank+1; k <= newLoserRank; k++) 
				{
					teams.at(k-1) = teams.at(k);
				}

				// Now we can put the winner and loser in their new spots
				teams.at(newLoserRank) = losers.at(record);
				teams.at(newWinnerRank) = winners.at(record);
			}
			else if ((not winnerIsFBS) && loserIsFBS) 
			{
				for (k = loserRank+1 ; k < NTEAMS; k++) 
				{
					teams.at(k-1) = teams.at(k);
				}
				teams.at(NTEAMS-1) = losers.at(record);
			}

		}

		// Save the results from this permutation
		for (j = 0; j < NTEAMS; j++) 
		{
			score = 1.0 - (double)j/(double)NTEAMS;
			avgRank[teams.at(j)] += score;
			ranks_all.at(i).at(teams.at(j)) += score;
		}
		
	}

	// Normalization
	for (i = 0; i < NTEAMS; i++) 
	{
		avgRank[teams.at(i)] /= (double)NRAND;
	}

	avgRankSorted = flip_map(avgRank);
	uncertainty = bootstrap_uncertainty(NTEAMS, bootstrap_n, NRAND, teams, ranks_all);
	output(avgRankSorted, uncertainty, outfile, plotfile);

	cout << "Ranking completed and stored in " << outfile << ". Plot data saved to " << plotfile << "." << endl;
	cout << "Check accuracy of non-FBS teams list stored at non-FBS.txt. If FBS teams found, modify rankings input file with correct names." << endl;

	return 0;
}

map <string, double> bootstrap_uncertainty(int NTEAMS, int bootstrap_n, int NRAND, vector <string> &teams,vector < map <string, double> > &ranks_all)
{

	int perm;
	map <string, double> ranks_bootavg;
	map <string, double> ranks_bootvar;
	map <string, double> uncertainty;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0,NRAND-1);
	vector < map <string, double> > ranks_boot(bootstrap_n);

	// Bootstrap uncertainty calculation
	for (int team_i = 0; team_i < NTEAMS; team_i++)
	{
		ranks_bootvar[teams.at(team_i)] = 0.0;
		ranks_bootavg[teams.at(team_i)] = 0.0;
		for (int boot_i = 0; boot_i < bootstrap_n; boot_i++)
		{
			ranks_boot.at(boot_i)[teams.at(team_i)] = 0.0;
		}
	}

	for (int boot_i = 0; boot_i < bootstrap_n; boot_i++)
	{
		cout << "Bootstrap iteration: " << boot_i << endl;

		/* Randomly select one of the permutations with replacement and get the ranks of all
		 * teams. Do this the same number of times as the original permutations. */
		for (int perm_i = 0; perm_i < NRAND; perm_i++)
		{
			perm = dist(gen);

			for (int team_i = 0; team_i < NTEAMS; team_i++)
			{
				ranks_boot.at(boot_i).at(teams.at(team_i)) += ranks_all.at(perm).at(teams.at(team_i));
			}
		}

		for (int team_i = 0; team_i < NTEAMS; team_i++)
		{
			ranks_boot.at(boot_i).at(teams.at(team_i)) /= (double)NRAND;
			ranks_bootavg[teams.at(team_i)] += ranks_boot.at(boot_i).at(teams.at(team_i));
		}
	}

	for (int team_i = 0; team_i < NTEAMS; team_i++)
	{
		ranks_bootavg[teams.at(team_i)] /= (double) bootstrap_n;
	}

	for (int boot_i = 0; boot_i < bootstrap_n; boot_i++)
	{
		for (int team_i = 0; team_i < NTEAMS; team_i++)
		{
			ranks_bootvar[teams.at(team_i)] += pow(ranks_bootavg[teams.at(team_i)] - ranks_boot.at(boot_i).at(teams.at(team_i)),2);
		}
	}

	for (int team_i = 0; team_i < NTEAMS; team_i++)
	{
		ranks_bootvar[teams.at(team_i)] /= (double) (bootstrap_n - 1);
		uncertainty[teams.at(team_i)] = sqrt(ranks_bootvar[teams.at(team_i)]);
	}

	return uncertainty;
}

void output(multimap<double,string> &avgRankSorted, map <string, double> &uncertainty, string outfile, string plotfile)
{
	ofstream oFS;
	oFS.open(outfile.c_str());
	oFS << fixed << setprecision(6);
	vector <string> team;
	vector <double> score;
	vector <double> score_uncertainty;

	/* Retrieve the keys from the iterator */
	// Reference:
	// http://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap
	for (map<double,string>::iterator it=avgRankSorted.begin(); it != avgRankSorted.end(); ++it) 
	{
		team.push_back(it->second);
		score.push_back(it->first);
		score_uncertainty.push_back(uncertainty[it->second]);
	}

	/* Cycle through them in reverse */
	oFS << " Rank | Team                       | Score      | Uncertainty" << endl;
	oFS << "------|----------------------------|------------|------------" << endl;
	for (int i = team.size()-1; i >= 0; i--)
	{
		oFS << right << setw(5) << team.size()-i << " | " << setw(25) << left << team.at(i) << " | " << right << setw(10) << score.at(i) << " | " << right << setw(10) << score_uncertainty.at(i) << endl;
	}

	oFS.close();

	oFS.open(plotfile.c_str());

	oFS << setprecision(3);
	for (int i = team.size()-1; i >= 0; i--)
	{
		oFS << team.size()-i << setw(25) << score.at(i) << setw(25) << score_uncertainty.at(i) << setw(25) << "\"" << team.size()-i << ". " << team.at(i) << " (" << score.at(i) << ")\"" << endl;
	}

	oFS.close();

	return;
}



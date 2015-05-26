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

const int bootstrap_n = 50;

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

int main(int argc, char *argv[]) 
{

	 /* 
	  * higher means less movementFactor per win/loss, lower means more
	  * movementFactor less than 2.0 means the two teams will pass each other
	  * movementFactor less than 1.0 means the two teams completely swap (too much
	  * incentive for teams that lose alot to have a couple of wins and be
	  * highly ranked).
	  */
	const double movementFactor = 4.0;
	const int maxOffset = 25;
	const int AVGS = 0;
	const int STDDEVS = 1;
	const int NRUNS = 2;
	int NRAND;
	int NTEAMS;
	bool winnerIsFBS;
	bool loserIsFBS;
	double offset;
	double toppoints;
	ifstream iFS;
	int frame;
	int frame_i;
	int i;
	int j;
	int k;
	int l;
	int x;
	int loserRank;
	int newLoserRank;
	int newWinnerRank;
	int winnerRank;
	map <string, double> avgRank;
	map <string, double> uncertainty;
	map <string, double> ranks_bootavg;
	map <string, double> ranks_bootvar;
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

	vector < map <string, double> > ranks_boot(NRAND);
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
			ranks_boot.at(i)[team] = 0.0;
		}
	}

	iFS.close();

	NTEAMS = teams.size();

	cout << "Number of teams: " << NTEAMS << endl;

	for (i = 0; i < NRAND; i++) 
	{

		cout << i << endl;

		random_shuffle(teams.begin(), teams.end());

		iFS.open(winslossfile.c_str());

		while (!iFS.eof()) 
		{

			getline(iFS,winner);
			getline(iFS,loser);
			getline(iFS,space);
			if (iFS.eof()) 
			{	
				break;
			}

			winnerIsFBS = false;
			loserIsFBS = false;
			for (j = 0; j < teams.size(); j++) 
			{

				if (teams.at(j) == winner) 
				{
					winnerRank = j; 
					winnerIsFBS = true;
				}
				if (teams.at(j) == loser) 
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
			 * of that, shift the other teams around the movement.
			 */
			if (winnerIsFBS && loserIsFBS && winnerRank > loserRank) 
			{
				offset = (winnerRank - loserRank) / movementFactor;
				if (offset > maxOffset)
				{	
					offset = maxOffset;
				}
				tmpWinner = teams.at(winnerRank);
				tmpLoser = teams.at(loserRank);
				newLoserRank = (loserRank + offset);
				newWinnerRank = (winnerRank - offset);
				if (newWinnerRank < 1) 
				{ 
					newWinnerRank = 1;
				}
				if (newLoserRank > NTEAMS) 
				{ 
					newLoserRank = NTEAMS;
				}
				if (newWinnerRank == newLoserRank) 
				{ 
					newWinnerRank = newLoserRank + 1;
				}
				for (k = winnerRank-1; k >= newWinnerRank; k--) 
				{
					teams.at(k+1) = teams.at(k);
				}
				for (k = loserRank+1; k <= newLoserRank; k++) 
				{
				teams.at(k-1) = teams.at(k);
				}
				teams.at(newLoserRank) = tmpLoser;
				teams.at(newWinnerRank) = tmpWinner;
			}
			if ((not winnerIsFBS) && loserIsFBS) 
			{
				for (k = loserRank+1 ; k < teams.size(); k++) 
				{
					teams.at(k-1) = teams.at(k);
				}
				teams.at(teams.size()-1) = loser;
			}

		}

		iFS.close();

		// Save the results from this permutation
		for (j = 0; j < teams.size(); j++) 
		{
			avgRank[teams.at(j)] += j;
			ranks_all.at(i).at(teams.at(j)) += j;
		}
		
	}

	// Normalization
	for (i = 0; i < teams.size(); i++) 
	{
		avgRank[teams.at(i)] /= (double)NRAND;
	}

	// Bootstrap uncertainty calculation
	for (j = 0; j < teams.size(); j++)
	{
		ranks_bootvar[teams.at(j)] = 0.0;
		ranks_bootavg[teams.at(j)] = 0.0;
	}
	for (i = 0; i < bootstrap_n; i++)
	{
		cout << i << endl;

		for (frame_i = 0; frame_i < NRAND; frame_i++)
		{
			frame = rand() % NRAND;

			for (j = 0; j < teams.size(); j++)
			{
				ranks_boot.at(i).at(teams.at(j)) += ranks_all.at(frame).at(teams.at(j));
			}
		}
		for (j = 0; j < teams.size(); j++)
		{
			ranks_boot.at(i).at(teams.at(j)) /= (double)NRAND;
			ranks_bootavg[teams.at(j)] += ranks_boot.at(i).at(teams.at(j));
		}
	}

	for (j = 0; j < teams.size(); j++)
	{
		ranks_bootavg[teams.at(j)] /= (double) bootstrap_n;
	}

	for (i = 0; i < bootstrap_n; i++)
	{
		for (j = 0; j < teams.size(); j++)
		{
			ranks_bootvar[teams.at(j)] += pow(ranks_bootavg[teams.at(j)] - ranks_boot.at(i).at(teams.at(j)),2);
		}
	}

	for (j = 0; j < teams.size(); j++)
	{
		ranks_bootvar[teams.at(j)] /= (double) (bootstrap_n - 1);
		uncertainty[teams.at(j)] = sqrt(ranks_bootvar[teams.at(j)]);
	}

	avgRankSorted = flip_map(avgRank);

	oFS << fixed << setprecision(6);

	oFS.open(outfile.c_str());

	// Reference:
	// http://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap
	i = 1;
	oFS << " Rank | Team                       | Score      | Uncertainty" << endl;
	oFS << "------|----------------------------|------------|------------" << endl;
	for (map<double,string>::iterator it=avgRankSorted.begin(); it != avgRankSorted.end(); ++it) 
	{
		oFS << right << setw(5) << i << " | " << setw(25) << left << it->second << " | " << right << setw(10) << it->first << " | " << right << setw(10) << uncertainty[it->second] << endl;
		i++;
	}

	oFS.close();

	oFS.open(plotfile.c_str());

	i = 1;
	oFS << setprecision(3);
	for (map<double,string>::iterator it=avgRankSorted.begin(); it != avgRankSorted.end(); ++it) 
	{
		oFS << i << setw(25) << it->first << setw(25) << uncertainty[it->second] << setw(25) << "\"" << i << ". " << it->second << " (" << it->first << ")\"" << endl;
		i++;
	}

	oFS.close();

	return 0;
}

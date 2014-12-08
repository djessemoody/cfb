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
std::pair<B,A> flip_pair(const std::pair<A,B> &p) {
    return std::pair<B,A>(p.second, p.first);
}

// Reference:
// http://stackoverflow.com/questions/5056645/sorting-stdmap-using-value
template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src) {
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

int main(int argc, char *argv[]) {

	 // higher means less movementFactor per win/loss, lower means more
	 // movementFactor less than 2.0 means the two teams will pass each other
	 // movementFactor less than 1.0 means the two teams completely swap (too much
	 // incentive for teams that lose alot to have a couple of wins and be
	 // highly ranked).
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
	map <string, double> stdDev;
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

	if (argc != 2) {
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

	iFS.open(teamsfile.c_str());

	// Read in the FBS teams from a file
	while(getline(iFS,team)) {
		teams.push_back(team);
		avgRank[team] = 0.0;
		stdDev[team] = 0.0;
	}

	iFS.close();

	NTEAMS = teams.size();

	cout << "Number of teams: " << NTEAMS << endl;

	// First run is for getting the mean
	// Second run is for getting the standard deviation
	for (x = 0; x < NRUNS; x++) {

		if (x == AVGS) cout << "Getting averages..." << endl;
		if (x == STDDEVS) cout << "Calculating standard deviations..." << endl;

		for (i = 0; i < NRAND; i++) {

			cout << i << endl;

			random_shuffle(teams.begin(), teams.end());

			iFS.open(winslossfile.c_str());

			while (!iFS.eof()) {

				getline(iFS,winner);
				getline(iFS,loser);
				getline(iFS,space);
				if (iFS.eof()) break;

				winnerIsFBS = false;
				loserIsFBS = false;
				for (j = 0; j < teams.size(); j++) {

					if (teams.at(j) == winner) {
						winnerRank = j; 
						winnerIsFBS = true;
					}
					if (teams.at(j) == loser) {
						loserRank = j;
						loserIsFBS = true;
					}
					if (loserIsFBS && winnerIsFBS) break;
				}

				// If both teams are FBS and the loser is more highly ranked than
				// the winner, the loser moves down and the winner moves up. You
				// can only move up or down the maximum offset. You can't move
				// up higher than number 1, and you can't be lower than the
				// number of teams. If you the team you beat is just above you,
				// you switch spots. If you play an FCS team and lose you go to
				// the bottom. After all of that, shift the other teams around
				// the movement.
				if (winnerIsFBS && loserIsFBS && winnerRank > loserRank) {
					offset = (winnerRank - loserRank) / movementFactor;
					if (offset > maxOffset) offset = maxOffset;
					tmpWinner = teams.at(winnerRank);
					tmpLoser = teams.at(loserRank);
					newLoserRank = (loserRank + offset);
					newWinnerRank = (winnerRank - offset);
					if (newWinnerRank < 1) newWinnerRank = 1;
					if (newLoserRank > NTEAMS) newLoserRank = NTEAMS;
					if (newWinnerRank == newLoserRank) newWinnerRank = newLoserRank + 1;
					for (k = winnerRank-1; k >= newWinnerRank; k--) {
						teams.at(k+1) = teams.at(k);
					}
					for (k = loserRank+1; k <= newLoserRank; k++) {
						teams.at(k-1) = teams.at(k);
					}
					teams.at(newLoserRank) = tmpLoser;
					teams.at(newWinnerRank) = tmpWinner;
				}
				if ((not winnerIsFBS) && loserIsFBS) {
					for (k = loserRank+1 ; k < teams.size(); k++) {
						teams.at(k-1) = teams.at(k);
					}
					teams.at(teams.size()-1) = loser;
				}

			}

			iFS.close();

			// Save the results from this permutation
			if (x == 0) {
				for (j = 0; j < teams.size(); j++) {
					avgRank[teams.at(j)] += j;
				}
			} else if (x == 1) {
				for (j = 0; j < teams.size(); j++) {
					stdDev[teams.at(j)] += pow(j-avgRank[teams.at(j)],2);
				}
			}
		
		}

		// Normalizations
		if (x == AVGS) {
			for (i = 0; i < teams.size(); i++) {
				avgRank[teams.at(i)] /= (double)NRAND;
			}
		} else if (x == STDDEVS) {
			for (i = 0; i < teams.size(); i++) {
				stdDev[teams.at(i)] /= ((double)NRAND-1.0);
				stdDev[teams.at(i)] = sqrt(stdDev[teams.at(i)]);
			}
		}

	}


	avgRankSorted = flip_map(avgRank);

	oFS << fixed << setprecision(6);

	oFS.open(outfile.c_str());

	// Reference:
	// http://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap
	i = 1;
	oFS << " Rank | Team                           | Score      | Std. Dev.  " << endl;
	oFS << "------|--------------------------------|------------|------------" << endl;
	for (map<double,string>::iterator it=avgRankSorted.begin(); it != avgRankSorted.end(); ++it) {
		oFS << right << setw(5) << i << " | " << setw(25) << left << it->second << " | " << right << setw(10) << it->first << " | " << right << setw(10) << stdDev[it->second] << endl;
		i++;
	}

	oFS.close();

	oFS.open(plotfile.c_str());

	i = 1;
	for (map<double,string>::iterator it=avgRankSorted.begin(); it != avgRankSorted.end(); ++it) {
		oFS << i << "  " << it->first << "  " << stdDev[it->second] << endl;
		i++;
	}

	oFS.close();

	return 0;
}

#CFB Rankings

##Rankings

This is a simple algorithm I developed for ranking college football teams. 
2014 rankings for each week are [here](https://github.com/wesbarnett/cfb/blob/master/2014/README.md).

##About

Preseason rankings can bias a computer poll's effectiveness. To overcome this,
this algorithm uses randomly generated 10,000 preaseason rankings. Only wins and
losses are counted in the algorithm (see below). It is designed in such a way
that strength of schedule is inherit, since losing to a lower ranked team causes
one to fall, and beating a higher ranked team causes one to rise. The
uncertainty analysis used allows one to see when error bars of a team's score
(it's rank) overlap, which indicate a statistical tie. Earlier weeks in a season
will result in a ranking where almost all teams are tied. After a few weeks
teams tend to group together. Eventually a few teams set themselves apart, and
the algorithm becomes more accurate as more data (more weeks of play) comes in.

##Algorithm

The following process is run 10,000 times using all data for the current season
to get the team's current score.

1. A preseason ranking of all FBS teams is randomly generated. 
2. Win/losses are read in for each week thus far in the season. 
3. Teams are then ranked for this iteration based on the following:
* If a team wins against a lower ranked team, nothing happens. 
* If a team wins against a higher ranked team, the higher team moves down and the lower teams moves up. The
higher team moves down the difference in ranks divided by 4; the lower team moves
up the difference in rank divided by 4. In both cases they can't move more than
25 spots per win/loss. 
* If a team loses to an FCS team they go to the bottom that
week. 
4. After the above movement occurs for all weeks, the rankings for this
   iteration are saved.

After these 10,000 iterations the rankings from each iteration is averaged for
each team and is the team's score (lower is better). Teams are then ranked by
their scores.  That is the final ranking. I also provide a [bootstrapped
uncertainty](https://en.wikipedia.org/wiki/Bootstrapping_(statistics)) analysis
with 50 iterations on the data generated. The uncertainty presented is the
bootstrap standard deviation.

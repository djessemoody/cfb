#CFB Rankings

##Rankings

This is a simple algorithm I developed for ranking college football teams. 
2014 rankings for each week are [here](https://github.com/wesbarnett/cfb/blob/master/2014/README.md).

##About

The following process is run 10,000 times. First, a randomly generated preseason
ranking of all FBS teams is generated. Then win/losses are read in for each
week. If a team wins against a lower ranked team, nothing happens. If a team wins against a
higher ranked team, the higher team moves down and the lower teams moves up. The
higher team moves down the difference in rank divided by 4; the lower team moves
up the difference in rank divided by 4. In both cases they can't move more than
25 spots per win/loss. If a team loses to an FCS team they go to the bottom that
week. The last week's ranking is saved.

After these 10,000 iterations the last week's ranking is averaged for each team
and is the team's score (lower is better). Teams are then ranked by their
scores.  That is the final ranking. I also provide a bootstrapped uncertainty
analysis.

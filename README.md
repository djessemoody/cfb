#CFB Rankings

##Rankings

This is a simple algorithm I developed for ranking college football teams. 
[View most recent rankings here](http://wesbarnett.github.io/cfb). Feedback,
forks, bug reports, pull requests welcome.

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
scores.  That is the final ranking. I also provide a standard deviation (which ends up
being quite large in my opinion except for the very worst teams).

As a reference, here is what the final ranking would be for the 2013 season for
the top 25 teams:

**2013**

 Rank | Team                      | Avg. Rank  | Std. Dev.  
------|---------------------------|------------|------------
    1 | Florida State |   9.994000 |  13.231453
    2 | Michigan State |  13.468000 |  15.343887
    3 | Auburn |  15.180000 |  15.357343
    4 | UCF |  16.846000 |  19.684851
    5 | Missouri |  18.238000 |  15.343220
    6 | South Carolina |  18.649000 |  16.579585
    7 | Stanford |  20.380000 |  16.365515
    8 | Oklahoma |  21.383000 |  18.088637
    9 | Clemson |  22.730000 |  19.928943
   10 | UCLA |  24.096000 |  18.956772
   11 | Alabama |  25.136000 |  21.115604
   12 | Louisville |  25.938000 |  26.140175
   13 | Ohio State |  25.962000 |  21.653550
   14 | LSU |  26.271000 |  21.013604
   15 | Oregon |  26.336000 |  20.627616
   16 | USC |  28.952000 |  20.430242
   17 | Notre Dame |  30.952000 |  22.041051
   18 | Texas A&M |  31.527000 |  22.881376
   19 | Oklahoma State |  31.608000 |  23.258028
   20 | Wisconsin |  31.900000 |  19.612665
   21 | Baylor |  32.129000 |  25.963576
   22 | Duke |  33.407000 |  20.726799
   23 | Nebraska |  34.505000 |  19.318145
   24 | Washington |  35.168000 |  26.147667
   25 | Penn State |  35.650000 |  23.231121

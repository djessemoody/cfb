
# This scrapes the records of FBS teams from the NCAA website. Although it fixes
# some names, you *MUST* verify that they are correct. At times there is a bug
# where a team name get abbreviated.

from lxml import html
import requests


def doScraping(f,year,week):

    strweek = week
    if week != "P":
        if int(week) < 10:
            strweek = "0" + week

    SCHEDURLBASE = "http://www.ncaa.com/scoreboard/football/fbs/"
    SCHEDURL = SCHEDURLBASE + str(year) + "/" + strweek
    print " Getting results for week " + str(week) + " from " + SCHEDURL + "."

    schedpage = requests.get(SCHEDURL)
    schedtree = html.fromstring(schedpage.text)
    schedteams = schedtree.xpath('//div[@class="team"]//a/@href')
    for y in range(0,len(schedteams)):
        schedteams[y] = schedteams[y][9:]

    finalscores = schedtree.xpath('//td[@class="final score"]/text()')
    if len(finalscores) == 0:
            print "No scores for week " + week
            return

    gameStatus = schedtree.xpath('//div[starts-with(@class,"game-status")]/text()')
    x = 0
    for y in range(0,len(schedteams)-1,2):
        if (gameStatus[y/2] != "canceled"):
            if int(finalscores[x]) > int(finalscores[x+1]):
                f.write(schedteams[y].rstrip()+'\n')
                f.write(schedteams[y+1].rstrip()+'\n\n')
            else:
                f.write(schedteams[y+1].rstrip()+'\n')
                f.write(schedteams[y].rstrip()+'\n\n')
            x += 2

thisweek = 15;
year = 2015;
f = open("winslosses.txt","w")
for week in range(1,thisweek+1):
    doScraping(f,year,str(week))
#doScraping(f,year,"P")

f.close();

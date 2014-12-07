
# This scrapes the records of FBS teams from the NCAA website. Although it fixes
# some names, you *MUST* verify that they are correct. At times there is a bug
# where a team name get abbreviated.

from lxml import html
import requests

def fixTeamNames(teamnames):

	for x in range(0,len(teamnames)):
		if teamnames[x] == "Ole Miss":
			teamnames[x] = "Mississippi"
		if teamnames[x] == "Mississippi St.":
			teamnames[x] = "Mississippi State"
		if teamnames[x] == "Washington St.":
			teamnames[x] = "Washington State"
		if teamnames[x] == "Colorado St.":
			teamnams[x] = "Colorado State"
		if teamnames[x] == "Northern Ill.":
			teamnames[x] = "Northern Illinois"
		if teamnames[x] == "Western Mich.":
			teamnames[x] = "Western Michigan"
		if teamnames[x] == "Eastern Mich.":
			teamnames[x] = "Eastern Michigan"
		if teamnames[x] == "Cent. Michigan":
			teamnames[x] = "Central Michigan"
		if teamnames[x] == "New Mexico St.":
			teamnames[x] = "New Mexico State"
		if teamnames[x] == "Appalachian St.":
			teamnames[x] = "Appalachian State"
		if teamnames[x] == "Middle Tenn.":
			teamnames[x] = "Middle Tennessee"
		if teamnames[x] == "La.-Monroe":
			teamnames[x] = "Louisiana-Monroe"
		if teamnames[x] == "La.-Lafayette":
			teamnames[x] = "Louisiana-Lafayette"
		if teamnames[x] == "Ark.-Pine Bluff":
			teamnames[x] = "Arkansas-Pine Bluff"
		if teamnames[x] == "Jacksonville St.":
			teamnames[x] = "Jacksonville State"
		if teamnames[x] == "Western Ky.":
			teamnames[x] = "Western Kentucky"
		if teamnames[x] == "Steph. F. Austin":
			teamnames[x] = "Stephen F. Austin State"
		if teamnames[x] == "South Dakota St.":
			teamnames[x] = "South Dakota State"
		if teamnames[x] == "North Dakota St.":
			teamnames[x] = "North Dakota State"
		if teamnames[x] == "Youngstown St.":
			teamnames[x] = "Youngstown State"
		if teamnames[x] == "Central Ark.":
			teamnames[x] = "Central Arkansas"
		if teamnames[x] == "Northern Ariz.":
			teamnames[x] = "Northern Arizona"
		if teamnames[x] == "Western Caro.":
			teamnames[x] = "Western Carolina"
		if teamnames[x] == "N.C. Central":
			teamnames[x] = "North Carolina Central"
		if teamnames[x] == "NC State":
			teamnames[x] = "North Carolina State"
		if teamnames[x] == "Ga. Southern":
			teamnames[x] = "Georgia Southern"
		if teamnames[x] == "FIU":
			teamnames[x] = "Florida International"
	
	return teamnames

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
	schedteams = schedtree.xpath('//div[@class="team"]//a/text()')
	finalscores = schedtree.xpath('//td[@class="final score"]/text()')
	gameStatus = schedtree.xpath('//div[starts-with(@class,"game-status")]/text()')

	schedteams = fixTeamNames(schedteams)

	x = 0
	for y in range(0,len(schedteams)-1,2):
		if (gameStatus[y/2] != "cancelled"):
			if int(finalscores[x]) > int(finalscores[x+1]):
				f.write(schedteams[y].rstrip()+'\n')
				f.write(schedteams[y+1].rstrip()+'\n\n')
			else:
				f.write(schedteams[y+1].rstrip()+'\n')
				f.write(schedteams[y].rstrip()+'\n\n')
			x += 2

thisweek = 14;
year = 2014;
f = open("week15.txt","w")
#for week in range(1,thisweek+1):
doScraping(f,year,str(15))

f.close();

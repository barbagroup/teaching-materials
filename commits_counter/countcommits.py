# coding: utf-8

# usage:
# python countcommits.py [handles_file]

import numpy
import requests
import sys
from bs4 import BeautifulSoup


def count_commits(github_id, daylim):
    """Return the number of commits associated with github_id within the past daylim days"""

    myurl = 'https://github.com/' + github_id
    r = requests.get(myurl)
    soup = BeautifulSoup(r.text, "lxml")
    glist = soup.findAll('g')
    
    # initialize the counter
    daycount = 0
    commitcount = 0
    
    for i in reversed( range(1, len(glist)) ):
        rectlist = glist[i].findAll('rect')
        for j in reversed( range(len(rectlist)) ):
            # 2: data-count, -1: "number", 1:-1: get rid of quotes
            daycount += 1
            if daycount <= daylim:
                commitcount += int( str(rectlist[j]).split()[2].split('=')[-1][1:-1] )
            else:
                return commitcount


def main():
    
    # read the file of the students' github handles
    datafile = open(sys.argv[1], 'r')
    lines = datafile.readlines()

    # build a list of their github handles
    github_ids = []
    for line in lines:
        github_ids.append(line)

    datafile.close()
    
    # remove the trailing '\n' in github_id
    for i in range(len(github_ids)):
        github_ids[i] = github_ids[i].replace('\n', '')

    # how many days to count back from today
    daylim = 7
    
    # initialize commits array
    commits = numpy.empty(len(github_ids), dtype=int)
    
    for i, github_id in enumerate(github_ids):
        commits[i] = count_commits(github_id, daylim)
    
    # output in format
    print('\n')
    print('%-20s %-10s' % ('Github-id', '#commits') )
    print('-----'*6)
    for i in range(commits.size):
        print('%-20s %-2i' % (github_ids[i], commits[i]) )
    print('\n')

    indices = numpy.where(commits == commits.max())[0]
    print("most commits: ")
    for index in indices:
        print("\t" + github_ids[index])
    indices = numpy.where(commits == commits.min())[0]
    print("least commits: ")
    for index in indices:
        print("\t" + github_ids[index])

    print('\n')
    
if __name__ == "__main__": main()
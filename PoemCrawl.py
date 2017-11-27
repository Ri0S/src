import requests
from bs4 import BeautifulSoup
import sys
import re
import os
#wr_id limit is 1~241211
URL = "http://www.poemlove.co.kr/bbs/board.php?bo_table=tb01&wr_id="

#return Poem Title-writer
def ParsePoem(Num):
    req = requests.get(URL+str(Num))
    html = req.text
    soup = BeautifulSoup(html, 'html.parser')
    result = soup.select("#content table:nth-of-type(1) strong")

    title = result[0].string
    writer = result[1].string
    #print writer

    result = soup.find_all("span","ct")

    if not os.path.exists(writer):
        os.makedirs(writer)

    
    f = open(writer+"/"+title+".txt","w")
    f.write(result[0].text.encode('utf8'))
    f.close()
    return title

def main():
    print "start"
    for i in range(1, 241216):
        try:
	    print "idx is %d" %(i)
            print ParsePoem(i)
        except:
            continue

    #print ParsePoem(2)
    #print ParsePoem(240000)


if __name__ == '__main__':
    main()

#Python program to scrape website 
#and save quotes from website
import requests
from bs4 import BeautifulSoup
import csv


def parseVerbForm(str):
    # Delete everything that is between < and >
    while str.find('<')>0:
        l = str.find('<')
        r = str.find('>')
        str = str[:l] + str[r+1:]
    if str[0]=='[': str = str[1:len(str)-1]
    # It could be that there are two forms, separated by a comma. We want to take the only the first one.
    commaLocation = str.find(',')
    if commaLocation>0: str = str[:commaLocation]
    return str


def gatherSixForms(request, searchString):
    lang = 'fr'
    res = [
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 1|s|" + searchString}))),
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 2|s|" + searchString}))),
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 3|s|" + searchString}))),
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 1|p|" + searchString}))),
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 2|p|" + searchString}))),
    parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang+" 3|p|" + searchString})))
    ]
    return res

def gatherSingleForms(request, searchString):
    lang = 'fr'
    return parseVerbForm(str(BeautifulSoup(request.content, 'html5lib').find_all('span', attrs = {'lang' : lang, 'class' : "Latn form-of lang-"+lang + " " + searchString})))

def getVerb(verb):
    URL = "https://en.wiktionary.org/wiki/" + verb
    r = requests.get(URL)
    verbTable = BeautifulSoup(r.content, 'html5lib').find_all('span', attrs = {'lang' : 'fr', 'class' : "Latn form-of lang-fr 1|s|pres|indc-form-of"})

    participe_passe         = gatherSingleForms(r, "pp-form-of")
    participe_present       = gatherSingleForms(r, "ppr-form-of")
    indicative_present      = gatherSixForms(r, "pres|indc-form-of")
    indicative_imparfait    = gatherSixForms(r, "impf|indc-form-of")
    passe_simple            = gatherSixForms(r, "phis-form-of")
    futur_simple            = gatherSixForms(r, "futr-form-of")
    conditionnel_simple     = gatherSixForms(r, "cond-form-of")
    subjunctive_present     = gatherSixForms(r, "pres|subj-form-of")
    subjunctive_imperf      = gatherSixForms(r, "impf|subj-form-of")
    imperative              = gatherSixForms(r, "impr-form-of")

    # Sitten tungetaan kaikki vaan pötköön
    
    res = [verb, participe_present, participe_passe]
    for e in indicative_present: res.append(e)
    for e in indicative_imparfait: res.append(e)
    for e in passe_simple: res.append(e)
    for e in futur_simple: res.append(e)
    for e in conditionnel_simple: res.append(e)
    for e in subjunctive_present: res.append(e)
    for e in subjunctive_imperf: res.append(e)
    for e in imperative: 
        if(e): res.append(e)

    #print("len=", len(res))
    return res
    #return [verb, participe_present, participe_passe, indicative_present, indicative_imparfait, passe_simple, futur_simple, conditionnel_simple, subjunctive_present, subjunctive_imperf, imperative]

# Read the verbs from verblist.txt
verblist = []
file_verblist = open("verblist.txt","r",encoding='utf-8')
for line in file_verblist:
    # Before appending, we need to fix the string
    verblist.append(line.rstrip())
file_verblist.close()

print("len(verblist)=", len(verblist))

demoverblist = [
        "acheter",
        "acquérir",
        "aimer",
        "aller",
]

file1 = open("verbtable.txt","w")

for e in verblist:
    res = str(getVerb(e))
    file1.write(str(res) + "\n")
    print("Wrote:", e)

file1.close()

print("All done!")
import time
import colorama
import pandas as pd
from datetime import datetime
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager
from colorama import Fore, Back, Style
from bs4 import BeautifulSoup

colorama.init()

URL = "https://coinmarketcap.com/"

FileName = str(datetime.now().date())+'.csv'

ColumnsName=['name','price','marketcap']

def CryptoParsing():
    LimitData=25
    Data=[]
    count=0
    driver = webdriver.Chrome(ChromeDriverManager().install())
    print('\033[2J')
    print('\033[H')
    driver.get(URL)
    print('\033[2J')
    print('\033[H')
    for heig_d in range(0, driver.execute_script("return document.body.scrollHeight"), 500):
        driver.execute_script(f"0,window.scrollTo(0, {heig_d});")
        print('\033[2J')
        print('\033[H')
        time.sleep(1)

    html = driver.page_source

    soup = BeautifulSoup(html, 'html.parser')
    items = soup.find(class_="bFzXgL").find_all('tr')
    for item in items:
        if (item.find(class_="iworPT") != None):
            item_name = item.find(class_='iworPT').text
            item_priсe = item.find(class_='cLgOOr').text
            item_marketcap = item.find(class_='iosgXe').text
            Data.append([item_name,item_priсe,item_marketcap])
            count+=1
            if(count==LimitData):
                break
    print('\033[2J')
    print('\033[H')
    return Data

def PrintCrypto(data):
    dataframe = pd.DataFrame(data,columns=ColumnsName)
    print(dataframe.head(25))

def SearchCrypto(data, key):
    items = []
    for item in data:
        if item[0].upper().startswith(key.upper()):
            items.append(item)
    return items

def CreateCSV(data):
    dataframe = pd.DataFrame(data,columns=ColumnsName)
    dataframe.to_csv(FileName, index=False, sep=';')

def LoadCSV():
    dataframe=pd.read_csv(FileName, sep=';')
    data=dataframe.values.tolist().copy()
    return data

def menu():
    CryptoCurrency = []
    while True:
        print("1. Parsing CryptoCurrency")
        print("2. Print CryptoCurrency")
        print("3. Search CryptoCurrency")
        print("4. Create CSV")
        print("5. Load today's CSV")
        print("0. Exit")
        sw = input("Select: ")
        print('\033[2J')
        print('\033[H')

        if sw == "1":
            try:
                CryptoCurrency=CryptoParsing()
                print("Parsing was completed")
            except Exception:
                CryptoCurrency.clear()
                print("Please try again")
        elif sw == "2":
            PrintCrypto(CryptoCurrency)
        elif sw == "3":
            key = input("Enter (name): ")
            Items=SearchCrypto(CryptoCurrency,key)
            if not Items:
                print("CryptoCurrency hasn't been found!!!")
            else:
                print()
                i=0
                print("{0:>21} {1:>15} {2:>15}".format(ColumnsName[0],ColumnsName[1],ColumnsName[2]))
                for item in SearchCrypto(CryptoCurrency,key):
                    print("{0}{1:>20} {2:>15} {3:>15}".format(i,item[0],item[1],item[2]))
                    i+=1
        elif sw == "4":
            CreateCSV(CryptoCurrency)
            print("File CSV was created")
        elif sw == "5":
            try:
                CryptoCurrency=LoadCSV()
                print("Loading was completed")
            except Exception:
                CryptoCurrency.clear()
                print("File CSV not found")
        elif sw == "0":
            break
        print()

print('\033[2J')
print('\033[H')
print('\033[32m')
menu()


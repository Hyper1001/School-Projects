command0 = """CREATE TABLE IF NOT EXISTS
customer(CUST_ID INTEGER PRIMARY KEY, NAME VARCHAR(50), PHONE VARCHAR(50))"""
crsr.execute(command0)

crsr.execute("""DELETE FROM customer""")

command1 = """CREATE TABLE IF NOT EXISTS
rental(CUST_ID INTEGER NOT NULL, VEHICLE_ID VARCHAR(50) NOT NULL, START_DATE INTEGER NOT NULL, ORDER_DATE INTEGER NOT NULL, RENTAL_TYPE INTEGER NOT NULL, QTY INTEGER NOT NULL, RETURN_DATE VARCHAR(50) NOT NULL, TOTAL_AMOUNT INTEGER NOT NULL, PAYMENT_DATE VARCHAR(50), FOREIGN KEY (CUST_ID) REFERENCES customer(CUST_ID), FOREIGN KEY (VEHICLE_ID) REFERENCES vehicle(VEHICLE_ID))"""
crsr.execute(command1)

crsr.execute("""DELETE FROM rental""")

command2 = """CREATE TABLE IF NOT EXISTS
vehicle(VEHICLE_ID VARCHAR(50) NOT NULL PRIMARY KEY, DESCRIPTION VARCHAR(50) NOT NULL, YEAR INTEGER NOT NULL, TYPE INTEGER NOT NULL, CATEGORY INTEGER NOT NULL, FOREIGN KEY (TYPE) REFERENCES rate(TYPE), FOREIGN KEY (CATEGORY) REFERENCES rate(CATEGORY))"""
crsr.execute(command2)

crsr.execute("""DELETE FROM vehicle""")

command3 = """CREATE TABLE IF NOT EXISTS
rate(TYPE INTEGER NOT NULL, CATEGORY INTEGER NOT NULL, WEEKLY INTEGER NOT NULL, DAILY INTEGER NOT NULL)"""
crsr.execute(command3)

crsr.execute("""DELETE FROM rate""")

#IMPORT DATA

with open('CUSTOMER.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['CustID'], i['Name'], i['Phone']) for i in dr]

crsr.executemany("INSERT INTO customer(CUST_ID, NAME, PHONE) VALUES (?, ?, ?);", to_db)

crsr.execute("""SELECT COUNT(*)
             FROM customer""")
print(crsr.fetchall())

with open('RENTAL.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['CustID'], i['VehicleID'], i['StartDate'], i['OrderDate'], i['RentalType'], i['Qty'], i['ReturnDate'], i['TotalAmount'], i['PaymentDate']) for i in dr]

crsr.executemany("INSERT INTO rental(CUST_ID, VEHICLE_ID, START_DATE, ORDER_DATE, RENTAL_TYPE, QTY, RETURN_DATE, TOTAL_AMOUNT, PAYMENT_DATE) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);", to_db)

crsr.execute("""SELECT COUNT(*)
             FROM rental""")
print(crsr.fetchall())

with open('VEHICLE.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['VehicleID'], i['Description'], i['Year'], i['Type'], i['Category']) for i in dr]

crsr.executemany("INSERT INTO vehicle(VEHICLE_ID, DESCRIPTION, YEAR, TYPE, CATEGORY) VALUES (?, ?, ?, ?, ?);", to_db)

crsr.execute("""SELECT COUNT(*)
             FROM vehicle""")
print(crsr.fetchall())

with open('RATE.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['Type'], i['Category'], i['Weekly'], i['Daily']) for i in dr]

crsr.executemany("INSERT INTO rate(TYPE, CATEGORY, WEEKLY, DAILY) VALUES (?, ?, ?, ?);", to_db)

crsr.execute("""SELECT COUNT(*)
             FROM rate""")
print(crsr.fetchall())

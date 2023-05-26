from tkinter import *
import sqlite3, csv

root = Tk()
root.title('Car Rental Database')

con = sqlite3.connect('test.db')

crsr = con.cursor()

# Create table
command0 = """CREATE TABLE IF NOT EXISTS
customer(CUST_ID INTEGER PRIMARY KEY, NAME VARCHAR(50), PHONE VARCHAR(50))"""
crsr.execute(command0)
crsr.execute("""DELETE FROM customer""")

command1 = """CREATE TABLE IF NOT EXISTS
rental(CUST_ID INTEGER NOT NULL, VEHICLE_ID VARCHAR(50) NOT NULL, START_DATE VARCHAR(50) NOT NULL, ORDER_DATE VARCHAR(50) NOT NULL, RENTAL_TYPE INTEGER NOT NULL, QTY INTEGER NOT NULL, RETURN_DATE VARCHAR(50) NOT NULL, TOTAL_AMOUNT INTEGER NOT NULL, PAYMENT_DATE VARCHAR(50), FOREIGN KEY (CUST_ID) REFERENCES customer(CUST_ID), FOREIGN KEY (VEHICLE_ID) REFERENCES vehicle(VEHICLE_ID))"""
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

# Import Data

with open('CUSTOMER.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['CustID'], i['Name'], i['Phone']) for i in dr]

crsr.executemany("INSERT INTO customer(CUST_ID, NAME, PHONE) VALUES (?, ?, ?);", to_db)

with open('RENTAL.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['CustID'], i['VehicleID'], i['StartDate'], i['OrderDate'], i['RentalType'], i['Qty'], i['ReturnDate'], i['TotalAmount'], i['PaymentDate']) for i in dr]

crsr.executemany("INSERT INTO rental(CUST_ID, VEHICLE_ID, START_DATE, ORDER_DATE, RENTAL_TYPE, QTY, RETURN_DATE, TOTAL_AMOUNT, PAYMENT_DATE) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);", to_db)

with open('VEHICLE.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['VehicleID'], i['Description'], i['Year'], i['Type'], i['Category']) for i in dr]

crsr.executemany("INSERT INTO vehicle(VEHICLE_ID, DESCRIPTION, YEAR, TYPE, CATEGORY) VALUES (?, ?, ?, ?, ?);", to_db)

with open('RATE.csv','r') as fin:
    dr = csv.DictReader(fin)
    to_db = [(i['Type'], i['Category'], i['Weekly'], i['Daily']) for i in dr]

crsr.executemany("INSERT INTO rate(TYPE, CATEGORY, WEEKLY, DAILY) VALUES (?, ?, ?, ?);", to_db)

#Query 1
crsr.execute("""ALTER TABLE RENTAL ADD COLUMN RETURNED INTEGER NOT NULL DEFAULT 1""")
crsr.execute("""UPDATE rental SET Returned = 0 WHERE PAYMENT_DATE = "NULL" """)

#Query 2
crsr.execute("""CREATE VIEW [QUERY 2] AS SELECT ORDER_DATE, START_DATE, RETURN_DATE, CASE WHEN RENTAL_TYPE=1 THEN QTY||' days' ELSE (QTY*7)||' days' END , rental.VEHICLE_ID, CASE TYPE WHEN '1' THEN 'Luxury' ELSE 'Basic' END, CASE CATEGORY WHEN '1' THEN 'Compact' WHEN '2' THEN 'Medium' WHEN '3' THEN 'Large' WHEN '4' THEN 'SUV' WHEN '5' THEN 'Truck' ELSE 'Van' END, rental.CUST_ID, NAME, TOTAL_AMOUNT, CASE RETURNED WHEN '1' THEN '$0' ELSE '$'||(TOTAL_AMOUNT) END FROM rental INNER JOIN vehicle ON rental.VEHICLE_ID = vehicle.VEHICLE_ID INNER JOIN customer ON rental.CUST_ID = customer.CUST_ID""")

crsr.execute("""SELECT * FROM [QUERY 2];""")



# Create submit function Customer
#1
def csubmit():
    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Insert into table
    crsr.execute("INSERT INTO customer VALUES (NULL, :NAME, :PHONE)",
        {
            
            'NAME':NAME.get(),
            'PHONE':PHONE.get()
        }
    
    )
    con.commit()
    con.close()

    # Clear text boxes
    NAME.delete(0,END)
    PHONE.delete(0,END)

# Create submit function Vehicle
#2
def vsubmit():
    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Insert into table
    crsr.execute("INSERT INTO vehicle VALUES (:VEHICLE_ID, :DESCRIPTION, :YEAR, :TYPE, :CATEGORY)",
        {
            'VEHICLE_ID':VEHICLE_ID.get(),
            'DESCRIPTION':DESCRIPTION.get(),
            'YEAR':YEAR.get(),
            'TYPE':TYPE.get(),
            'CATEGORY':CATEGORY.get()
        }
    
    )
    con.commit()
    con.close()

    # Clear text boxes
    VEHICLE_ID.delete(0,END)
    DESCRIPTION.delete(0,END)
    YEAR.delete(0,END)
    TYPE.delete(0,END)
    CATEGORY.delete(0,END)

#3
def rsubmit():
    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Insert into table
    
    crsr.execute("SELECT vehicle.VEHICLE_ID FROM vehicle WHERE vehicle.VEHICLE_ID NOT IN (SELECT VEHICLE_ID FROM rental WHERE RETURNED = 0 GROUP BY VEHICLE_ID) AND TYPE = :TYPE AND CATEGORY = :CATEGORY LIMIT 1",
        {
            'TYPE':TYPE1.get(),
            'CATEGORY':CATEGORY1.get()
        }
    )
    
    CAR = crsr.fetchone()[0]
    
    crsr.execute("INSERT INTO rental VALUES (:CUST_ID, :VEHICLE_ID, :START_DATE, :ORDER_DATE, :RENTAL_TYPE, :QUANTITY, :RETURN_DATE, :TOTAL_AMOUNT, :PAYMENT_DATE, 0)",
        {
            'CUST_ID':CUST_ID_RENTAL.get(),
            'VEHICLE_ID':CAR,
            'START_DATE':START_DATE.get(),
            'ORDER_DATE':ORDER_DATE.get(),
            'RENTAL_TYPE':RENTAL_TYPE.get(),
            'QUANTITY':QUANTITY.get(),
            'RETURN_DATE':RETURN_DATE.get(),
            'TOTAL_AMOUNT':TOTAL_AMOUNT.get(),
            'PAYMENT_DATE':PAYMENT_DATE.get(),
        }
    
    )
    
    con.commit()
    con.close()

    # Clear text boxes
    CUST_ID_RENTAL.delete(0,END)
    START_DATE.delete(0,END)
    ORDER_DATE.delete(0,END)
    RENTAL_TYPE.delete(0,END)
    QUANTITY.delete(0,END)
    RETURN_DATE.delete(0,END)
    TOTAL_AMOUNT.delete(0,END)
    PAYMENT_DATE.delete(0,END)
    TYPE1.delete(0,END)
    CATEGORY1.delete(0,END)
    
#4
def returnrental():
    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Insert into table
    
    crsr.execute("SELECT TOTAL_AMOUNT FROM rental WHERE ",
        {
            'TYPE':TYPE1.get(),
            'CATEGORY':CATEGORY1.get()
        }
    )

# Create customer query function 
# Create customer query function
def cquery():
    cquery_list = Tk()
    cquery_list.title("List All Customers")
    cquery_list.geometry("400x800")

    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Query the database
    crsr.execute("SELECT * FROM customer")
    records = crsr.fetchall()
    print(records)

    # Loop through records
    for index, x in enumerate(records):
        num = 0
        for y in x:
            lookup_label = Label(cquery_list, text=y)
            lookup_label.grid(row=index, column=num)
            num += 1

    con.commit()
    con.close()

# Create vehicle query function
def vquery():
    vquery_list = Tk()
    vquery_list.title("List All Vehicles")
    vquery_list.geometry("400x600")

    con = sqlite3.connect('test.db')
    crsr = con.cursor()

    # Query the database
    crsr.execute("SELECT * FROM vehicle")
    records = crsr.fetchall()
    print(records)

    # Loop through records
    for index, x in enumerate(records):
        num = 0
        for y in x:
            lookup_label = Label(vquery_list, text=y)
            lookup_label.grid(row=index, column=num)
            num += 1

    con.commit()
    con.close()

# Create text boxes Customer
NAME = Entry(root, width=30)
NAME.grid(row = 1, column = 1, padx=20)
PHONE = Entry(root, width=30)
PHONE.grid(row = 2, column = 1, padx=20)

# Create text boxes Vehicle
VEHICLE_ID = Entry(root, width=30)
VEHICLE_ID.grid(row = 0, column = 4, padx=20)
DESCRIPTION = Entry(root, width=30)
DESCRIPTION.grid(row = 1, column = 4, padx=20)
YEAR = Entry(root, width=30)
YEAR.grid(row = 2, column = 4, padx=20)
TYPE = Entry(root, width=30)
TYPE.grid(row = 3, column = 4, padx=20)
CATEGORY = Entry(root, width=30)
CATEGORY.grid(row = 4, column = 4, padx=20)

# Create text boxes Rental
CUST_ID_RENTAL = Entry(root, width=30)
CUST_ID_RENTAL.grid(row = 0, column = 7, padx=20)
START_DATE = Entry(root, width=30)
START_DATE.grid(row = 1, column = 7, padx=20)
ORDER_DATE = Entry(root, width=30)
ORDER_DATE.grid(row = 2, column = 7, padx=20)
RENTAL_TYPE = Entry(root, width=30)
RENTAL_TYPE.grid(row = 3, column = 7, padx=20)
QUANTITY = Entry(root, width=30)
QUANTITY.grid(row = 4, column = 7, padx=20)
RETURN_DATE = Entry(root, width=30)
RETURN_DATE.grid(row = 5, column = 7, padx=20)
TOTAL_AMOUNT = Entry(root, width=30)
TOTAL_AMOUNT.grid(row = 6, column = 7, padx=20)
PAYMENT_DATE = Entry(root, width=30)
PAYMENT_DATE.grid(row = 7, column = 7, padx=20)
TYPE1 = Entry(root, width=30)
TYPE1.grid(row = 8, column = 7, padx=20)
CATEGORY1 = Entry(root, width=30)
CATEGORY1.grid(row = 9, column = 7, padx=20)

# Create text box labels Customer
CUST_ID_label = Label(root, text = "Customer ID")
CUST_ID_label.grid(row=0, column=0)
NAME_label = Label(root, text = "Name")
NAME_label.grid(row=1, column=0)
PHONE_label = Label(root, text = "Phone")
PHONE_label.grid(row=2, column=0)

# Create text box labels Vehicle
VEHICLE_ID_label = Label(root, text = "Vehicle ID")
VEHICLE_ID_label.grid(row=0, column=3)
DESCRIPTION_label = Label(root, text = "Description")
DESCRIPTION_label.grid(row=1, column=3)
YEAR_label = Label(root, text = "Year")
YEAR_label.grid(row=2, column=3)
TYPE_label = Label(root, text = "Type")
TYPE_label.grid(row=3, column=3)
CATEGORY_label = Label(root, text = "Category")
CATEGORY_label.grid(row=4, column=3)

# Create text box labels Rental
CUST_ID_RENTAL_label = Label(root, text = "Customer ID")
CUST_ID_RENTAL_label.grid(row=0, column=6)
START_DATE_label = Label(root, text = "Start Date")
START_DATE_label.grid(row=1, column=6)
ORDER_DATE_label = Label(root, text = "Order Date")
ORDER_DATE_label.grid(row=2, column=6)
RENTAL_TYPE_label = Label(root, text = "Rental Type")
RENTAL_TYPE_label.grid(row=3, column=6)
QUANTITY_label = Label(root, text = "Quantity")
QUANTITY_label.grid(row=4, column=6)
RETURN_DATE_label = Label(root, text = "Return Date")
RETURN_DATE_label.grid(row=5, column=6)
TOTAL_AMOUNT_label = Label(root, text = "Total Amount")
TOTAL_AMOUNT_label.grid(row=6, column=6)
PAYMENT_DATE_label = Label(root, text = "Payment Date")
PAYMENT_DATE_label.grid(row=7, column=6)
TYPE1_label = Label(root, text = "Type")
TYPE1_label.grid(row=8, column=6)
CATEGORY1_label = Label(root, text = "Category")
CATEGORY1_label.grid(row=9, column=6)

# Create submit button Customer
csubmit_btn = Button(root, text="Add Customer to Database", command=csubmit)
csubmit_btn.grid(row=6, column=0, columnspan=2, pady=10, padx=10, ipadx=100)

# Create submit button Vehicle
vsubmit_btn = Button(root, text="Add Vehicle to Database", command=vsubmit)
vsubmit_btn.grid(row=6, column=3, columnspan=2, pady=10, padx=10, ipadx=100)

# Create submit button Rental
rsubmit_btn = Button(root, text="Add Rental to Database", command=rsubmit)
rsubmit_btn.grid(row=10, column=6, columnspan=2, pady=10, padx=10, ipadx=100)

# Create customer query button
cquery_btn = Button(root, text="Show Customer Records", command=cquery)
cquery_btn.grid(row=7, column=0, columnspan=2, pady=10, padx=10, ipadx=100)

# Create vehicle query button
vquery_btn = Button(root, text="Show Vehicle Records", command=vquery)
vquery_btn.grid(row=7, column=3, columnspan=2, pady=10, padx=10, ipadx=100)

# Save (commit) the changes
con.commit()

# We can also close the connection if we are done with it.
# Just be sure any changes have been committed or they will be lost.
con.close()
root.mainloop()
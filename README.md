🛒✨ Inventory Billing System (C Language)

💡 A simple, efficient, and file-based billing system developed in C for small shops and academic projects.

📖 About the Project

The Inventory Billing System is a console-based application built using C programming language.
It helps in managing inventory items, generating customer bills, and updating stock automatically using file handling.

This project demonstrates real-world billing logic with a clean and structured approach.

🌟 Key Highlights

✔ Easy to use console interface
✔ Real-time inventory management
✔ Automatic bill calculation
✔ Unique Order ID for every bill
✔ Stock update after billing
✔ Edit & delete items before confirmation
✔ Clean and professional bill format

⚙️ Features

🟢 Add new items to inventory
🟢 Update stock, price, name, and category
🟢 View complete inventory list
🟢 Generate customer bill
🟢 Edit quantity during billing
🟢 Delete items from bill
🟢 Automatic stock reduction
🟢 File-based data storage

🧠 How the System Works
🔹 Step 1: Main Menu

User is presented with the following options:

➕ Add Item

📋 View Inventory

🧾 Generate Bill

❌ Exit

🔹 Step 2: Add Item

User enters Item ID, Name, Category, Price, and Stock

If Item ID already exists:

Stock is increased

Price and details are updated

Data is stored securely in inventory.txt

🔹 Step 3: View Inventory

Displays all available items with:

Item ID

Item Name

Category

Price

Stock

🔹 Step 4: Generate Bill

System generates a unique Order ID

User selects number of different items

Enters Item ID and quantity

System checks stock availability automatically

🔹 Step 5: Bill Editing Options

Before final confirmation, user can:
1️⃣ Edit item quantity
2️⃣ Delete item from bill
3️⃣ Confirm bill

A live bill preview is shown after every action.

🔹 Step 6: Final Bill Generation

Inventory stock is updated

🧾 Sample Output (Billing Format)

================= 🏪 DELHI SHOP BILL 🏪 =================
🧾 Order ID: 1025
---------------------------------------------------------
ID    Item            Category     Qty   Total
---------------------------------------------------------
101   Rice            Grocery      2     120.00
205   Soap            Household    3     90.00
310   Milk            Dairy        1     55.00
---------------------------------------------------------
💰 GRAND TOTAL:                       265.00
=========================================================
🙏 Thank You! Visit Again 😊

Final bill is displayed in a professional billing format

Order ID is saved for future reference

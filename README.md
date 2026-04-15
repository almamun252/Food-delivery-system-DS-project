# 🍔 Online Food Delivery System (C Language)

A console-based **Online Food Delivery System** developed using **C programming language** as a Data Structure Lab project.
The system simulates a real food delivery platform where users can browse restaurants, order food, rate restaurants, and receive deliveries from the nearest rider.

This project demonstrates the use of **Graph, Queue, and Heap data structures** in a practical application.

---

# 📌 Features

### 👤 User System

* Create account (username + phone + password)
* Login using **username or phone number**
* Secure login validation

### 🍽 Restaurant System

* View all restaurants
* Add / remove restaurants (admin)
* Change restaurant location
* Rate restaurants (1–5 stars)
* View **top rated restaurants**

### 🍔 Food Menu

* View dishes
* Add / delete dishes (admin)

### 🛵 Rider System

* Add rider
* View rider information
* Automatic rider selection based on shortest path

### 📦 Order System

* Add items to cart
* Order from multiple restaurants
* Delivery charge calculation:

```
Delivery charge = 50 Tk per restaurant
```

Example:

```
2 restaurants → 100 Tk delivery
```

* Order history tracking

### 🚚 Smart Delivery

The system selects the **best rider** based on the shortest total distance:

```
Rider → Restaurant → Customer
```

---

# 🧠 Data Structures Used

## 1️⃣ Graph

Used to calculate the **shortest delivery path** using **Dijkstra's Algorithm**.

Example usage:

* Rider to restaurant distance
* Restaurant to customer distance

```
Shortest Path → Faster Delivery
```

---

## 2️⃣ Queue

Used for **Order Processing (FIFO scheduling)**.

```
Customer Order
     ↓
   Enqueue
     ↓
   Order Queue
     ↓
  Dequeue (Processing)
```

Ensures orders are processed in the **same order they are received**.

---

## 3️⃣ Heap (Max Heap)

Used to maintain **Top Rated Restaurants**.

```
Highest Rating Restaurant
        ↓
      Max Heap
```

Operations used:

* Insert
* Extract Max

This allows quick retrieval of the **highest rated restaurants**.

---

# 📂 Project Structure

```
food_delivery_system
│
├── main.c
├── admin.c
├── user.c
├── order.c
├── restaurant.c
├── dish.c
├── rider.c
├── graph.c
├── location.c
│
├── users.txt
├── restaurants.txt
├── dishes.txt
├── riders.txt
├── locations.txt
├── graph.txt
│
└── README.md
```

---

# ⚙️ How to Compile & Run

### Compile

```
gcc *.c -o foodapp
```

### Run

```
./foodapp
```

or (Windows)

```
foodapp.exe
```

---

# 👨‍💻 Admin Login

```
Username: admin
Password: 12345
```

Admin can:

* Add / remove restaurants
* Manage dishes
* Manage riders
* Change restaurant location

---

# 📊 Example System Flow

```
User Login
     ↓
Browse Restaurants
     ↓
Select Food
     ↓
Add to Cart
     ↓
Order Queue (FIFO)
     ↓
Shortest Rider Selected (Graph)
     ↓
Delivery Completed
```

---

# 🎓 Academic Purpose

This project was developed as part of a **Data Structures Lab Project** to demonstrate real-world applications of:

* Graph Algorithms
* Priority Queue (Heap)
* Queue (FIFO Scheduling)

---

# 🚀 Future Improvements

Possible enhancements:

* GUI interface
* Database integration
* Live order tracking
* Dynamic delivery pricing
* Multiple rider assignment

---

# 👨‍💻 Developer

**MD Mustafizur Rahman**

Data Structure Lab Project
Department of Computer Science

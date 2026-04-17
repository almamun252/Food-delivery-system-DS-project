# 🍔 Online Food Delivery System (Data Structure Project)

## Project Overview
This project is a console-based **Online Food Delivery System** developed using the C programming language.  
The main goal of this project is to demonstrate the practical application of important data structures such as **Graph, Queue, and Heap** in a real-world scenario.

The system allows users to create accounts, browse restaurants, order food, rate restaurants, and manage delivery through optimized algorithms.

---

## 👨‍💻 Group Members

| Name |
|------|
| Abdullah Al Mamun |
| Md. Humaun Kobir Hasnat |
| Sayeed Al Sahab |
| Saidul Islam Sifat |
| Shahriar Hasan Joy |

---

##  Features

### 👤 User Features
- Create Account & Login
- View Restaurants
- View Top Rated Restaurants (Heap)
- View Food Menu
- Order Food
- Rate Restaurant
- View Order History

###  Admin Features
- Add / Remove Restaurant
- Change Restaurant Location
- Add / Delete Dish
- View Dishes
- Add Rider
- View Riders
- View Top Rated Restaurants

---

##  Data Structures Used

###  Graph
- Represents locations and distances
- Uses **Dijkstra’s Algorithm** for shortest path calculation
- Helps assign the most efficient delivery rider

###  Queue
- Used for **order processing (FIFO)**
- Ensures fair and sequential handling of customer orders

###  Max Heap
- Used to maintain restaurant ratings
- Quickly retrieves top-rated restaurants

---

##  Technologies Used

- Programming Language: **C**
- Compiler: **GCC**
- IDE: **Visual Studio Code**
- Operating System: **Windows**

---

## 📂 Project Structure

- main.c → Program control flow
- user.c → User management
- restaurant.c → Restaurant & rating system
- dish.c → Food menu management
- order.c → Order & queue processing
- rider.c → Rider management
- graph.c → Shortest path (Dijkstra)
- admin.c → Admin panel
- location.c → Location management

.txt files → Data storage (users, restaurants, dishes, riders, etc.)


---

## ▶ How to Run

```bash
gcc *.c -o foodapp
.\foodapp.exe
```

---

## System Workflow

User → Login/Register  
→ Select Restaurant  
→ Select Food  
→ Order Processing (Queue)  
→ Delivery Optimization (Graph - Dijkstra)  
→ Rider Assignment  
→ Delivery Completed

---

## Key Highlights

- Efficient rider assignment using Graph (Dijkstra)
- Fair order processing using Queue (FIFO)
- Fast restaurant ranking using Max Heap
- Modular and maintainable code structure

---
## References
- Cormen, T. H. et al. Introduction to Algorithms
- Goodrich, M. T. et al. Data Structures and Algorithms in C++
- Sedgewick, R. & Wayne, K. Algorithms
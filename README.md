# 🧩 C++ REST API with Crow Framework

A lightweight, multithreaded RESTful API built in modern C++ using the [Crow](https://github.com/ipkn/crow) microframework.  
This project demonstrates full CRUD operations on a simple product inventory — designed to be modular, thread-safe, and DevOps-friendly.

---

## 🚀 Features

- ✅ Built with C++17
- ⚡ Powered by [Crow](https://github.com/ipkn/crow)
- 🧵 Thread-safe with `std::mutex`
- 🔁 Complete CRUD (GET, POST, PUT, DELETE)
- 🧱 Modular design using a `ProductManager` class
- 🧪 Curl-tested endpoints
- 📦 Prepared for Docker deployment
- 📘 MIT Licensed

---

## 📁 Folder Structure

```
cppRestApi/
├── include/              # Header files
│   └── product_manager.h
├── src/                  # Source files
│   └── product_manager.cpp
├── main.cpp              # Entry point
├── CMakeLists.txt
├── README.md
├── LICENSE
├── .gitignore
└── build/                # Ignored build folder
```

---

## ⚙️ Build Instructions

### 1. Clone this repo
```bash
git clone https://github.com/rockorg98/cpp-rest-api.git
cd cpp-rest-api
```

### 2. Create build folder and compile
```bash
mkdir build && cd build
cmake ..
make
```

### 3. Run the server
```bash
./cppRestApi
```

> Server will start at `http://localhost:8080`

---

## 🧪 API Endpoints

### 🔍 Get all products
```bash
curl http://localhost:8080/products
```

### 🔍 Get product by ID
```bash
curl http://localhost:8080/product/1
```

### ➕ Add a product
```bash
curl -X POST http://localhost:8080/add_product \
     -H "Content-Type: application/json" \
     -d '{"name": "Milk", "price": 45}'
```

### ♻️ Update product
```bash
curl -X PUT http://localhost:8080/product/1 \
     -H "Content-Type: application/json" \
     -d '{"name": "Milk Updated", "price": 50}'
```

### ❌ Delete product
```bash
curl -X DELETE http://localhost:8080/product/1
```

---

## 🧠 Concepts Covered

- C++ REST API architecture using Crow
- JSON parsing and validation
- HTTP methods and route parameters
- Thread safety with `std::mutex`
- Git-based version control
- Project modularization

---

## 📌 Roadmap

This is part of a structured **28-day C++ Dev + DevOps roadmap**.  

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](./LICENSE) file for details.

---

## 🤝 Author

**rockorg98**  
C++ Developer | Systems Enthusiast | Learning DevOps  
[GitHub](https://github.com/rockorg98)  

# ⚽ Smart Football Competition Center

A modern, desktop-based football tournament management system built using **Qt (C++)** and **MySQL**. This app enables you to manage matches, teams, players, fields, and receive match-specific insights via a sleek and intuitive UI.

---

## 🖼️ Features

- Sidebar navigation for seamless access to key sections.
- Add and delete football matches dynamically.
- MySQL database integration to persist match data.
- Scrollable list of beautifully styled match cards.
- Clean and responsive UI built with Qt Widgets.

---

## 🚀 Getting Started

### 📦 Prerequisites

- Qt 6 or Qt 5.15+ installed (with Qt Creator recommended)
- MySQL Server installed and running
- MySQL user and database created

---

### 🗃️ Database Setup

1. Start your MySQL server.
2. Open MySQL terminal or your favorite client (e.g., DBeaver, MySQL Workbench).
3. Run the following SQL to create the required database and table:

```sql
CREATE DATABASE Smart_Football_Competition_Center;

USE Smart_Football_Competition_Center;

CREATE TABLE matches (
    id INT AUTO_INCREMENT PRIMARY KEY,
    team1 VARCHAR(100) NOT NULL,
    team2 VARCHAR(100) NOT NULL,
    time VARCHAR(10) NOT NULL,
    terrain VARCHAR(100) NOT NULL
);
```

4. Create a MySQL user if you don’t have one already:

```sql
CREATE USER 'mohamed'@'localhost' IDENTIFIED BY 'azerfy';
GRANT ALL PRIVILEGES ON Smart_Football_Competition_Center.* TO 'mohamed'@'localhost';
FLUSH PRIVILEGES;
```

🔐 **Note:** Replace `'mohamed'` and `'azerfy'` with your own credentials if needed.

---

### 🛠️ Build & Run

1. Clone this repository:

```bash
git clone https://github.com/yourusername/Football_Competition_Center.git
cd Football_Competition_Center
```

2. Open the `.pro` or main `.cpp` file using Qt Creator.
3. Build the project using `Ctrl + B` and run it with `Ctrl + R`.

---

### 📸 UI Preview

![Screenshot from 2025-04-18 01-29-56](https://github.com/user-attachments/assets/3d6e3b8c-511b-4cdc-9b8f-19f21c8d64bb)

---

### 🧠 Technologies Used

- Qt Widgets (C++)
- MySQL (via Qt SQL module)
- Qt Designer (for visual layout)
- Qt Resource System (for managing images and icons)


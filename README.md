# 🔐 Password Manager in C

A command-line based password manager built using C that allows users to securely store and manage their credentials with encryption, hashing, and backup mechanisms.

---

## 🚀 Features

- 👤 User Signup & Login
- 🔑 Master Key-based Encryption
- 🔒 Password Hashing using SHA-256
- ➕ Add Credentials (Website, Username, Password)
- 📄 View Stored Credentials (Decrypted)
- 🔍 Search Credentials
- ✏️ Update Credentials
- ❌ Delete Credentials
- 💾 Automatic Backup & Restore
- 🛡️ Data Integrity Check using Checksum

---

## 🧠 How It Works

- Each user has a separate file:  
  `users_<username>.csv`

- Stored format:

- Passwords are:
- Encrypted using XOR cipher with a master key
- Converted to HEX before storage

- On login:
- User enters master key
- Data is verified using checksum
- If corrupted → restored from backup

---

## 📂 Project Structure

---

## 🔐 Security Details

- **Hashing Algorithm**: SHA-256 (via OpenSSL)
- **Encryption**: XOR-based symmetric encryption
- **Integrity Check**: Checksum comparison between main file and backup

---

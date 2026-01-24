const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

// Path to patients.txt in C source files
const patientsFile = path.join(__dirname, '..', 'C source files', 'patients.txt');

app.use(bodyParser.json());
app.use(express.static('public'));

// Serve the HTML file
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

// Login endpoint
app.post('/login', (req, res) => {
  const { username, password } = req.body;
  fs.readFile(patientsFile, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ success: false, message: 'Error reading file' });
    }
    const lines = data.trim().split('\n');
    let found = false;
    for (let line of lines) {
      const parts = line.split(' ');
      if (parts.length >= 6) {
        const [name, age, gender, contact, user, pass] = parts;
        if (user === username && pass === password) {
          found = true;
          break;
        }
      }
    }
    if (found) {
      res.json({ success: true, message: 'Login successful' });
    } else {
      res.json({ success: false, message: 'Invalid credentials' });
    }
  });
});

// Register endpoint
app.post('/register', (req, res) => {
  const { name, age, gender, contact, username, password } = req.body;
  // Validation matching patient.c
  if (!name) {
    return res.json({ success: false, message: 'Invalid name. Name cannot be empty.' });
  }
  if (age < 1 || age > 120) {
    return res.json({ success: false, message: 'Invalid age. Age must be between 1 and 120.' });
  }
  if (gender !== 'Male' && gender !== 'Female') {
    return res.json({ success: false, message: 'Invalid gender. Please enter Male or Female.' });
  }
  if (!contact) {
    return res.json({ success: false, message: 'Invalid contact. Contact cannot be empty.' });
  }
  if (!username) {
    return res.json({ success: false, message: 'Invalid username. Username cannot be empty.' });
  }
  if (!password) {
    return res.json({ success: false, message: 'Invalid password. Password cannot be empty.' });
  }

  // Check if username already exists
  fs.readFile(patientsFile, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ success: false, message: 'Error reading file' });
    }
    const lines = data.trim().split('\n');
    for (let line of lines) {
      const parts = line.split(' ');
      if (parts.length >= 6 && parts[4] === username) {
        return res.json({ success: false, message: 'Username already exists' });
      }
    }
    // Append new patient in the same order as patient.c: name age gender contact username password
    const newLine = `${name} ${age} ${gender} ${contact} ${username} ${password}\n`;
    fs.appendFile(patientsFile, newLine, (err) => {
      if (err) {
        return res.status(500).json({ success: false, message: 'Error saving patient' });
      }
      res.json({ success: true, message: 'Registration successful' });
    });
  });
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
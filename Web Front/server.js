const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

// Path to patients.txt in C source files
const patientsFile = path.join(__dirname, '..', 'C source files', 'patients.txt');
const appointmentsFile = path.join(__dirname, '..', 'C source files', 'appointments.txt');
const medicalFile = path.join(__dirname, '..', 'C source files', 'medical_records.txt');

app.use(bodyParser.json());
app.use(express.static('public'));

// Serve the HTML file
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.get('/login', (req, res) => {
  res.sendFile(path.join(__dirname, 'login.html'));
});

app.get('/register', (req, res) => {
  res.sendFile(path.join(__dirname, 'register.html'));
});

app.get('/dashboard', (req, res) => {
  res.sendFile(path.join(__dirname, 'dashboard.html'));
});

app.get('/profile', (req, res) => {
  res.sendFile(path.join(__dirname, 'profile.html'));
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
    // Append new patient in the same order as patient.c: name age gender contact username password totalDueCharges
    const newLine = `${name} ${age} ${gender} ${contact} ${username} ${password} 0.00\n`;
    fs.appendFile(patientsFile, newLine, (err) => {
      if (err) {
        return res.status(500).json({ success: false, message: 'Error saving patient' });
      }
      res.json({ success: true, message: 'Registration successful' });
    });
  });
});

// API endpoints for dashboard
app.get('/api/profile', (req, res) => {
  const { username } = req.query;
  fs.readFile(patientsFile, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ error: 'Error reading file' });
    }
    const lines = data.trim().split('\n');
    for (let line of lines) {
      const parts = line.split(' ');
      if (parts.length >= 7 && parts[4] === username) {
        const [name, age, gender, contact, user, pass, totalDueCharges] = parts;
        return res.json({ name, age, gender, contact, totalDueCharges });
      }
    }
    res.status(404).json({ error: 'Patient not found' });
  });
});

app.get('/api/appointments', (req, res) => {
  const { username } = req.query;
  fs.readFile(appointmentsFile, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ error: 'Error reading file' });
    }
    const lines = data.trim().split('\n');
    const appointments = [];
    for (let line of lines) {
      const parts = line.split(' ');
      if (parts.length >= 4 && parts[0] === username) {
        const [, date, time, doctor] = parts;
        appointments.push({ date, time, doctor });
      }
    }
    res.json(appointments);
  });
});

app.get('/api/medical', (req, res) => {
  const { username } = req.query;
  fs.readFile(medicalFile, 'utf8', (err, data) => {
    if (err) {
      return res.status(500).json({ error: 'Error reading file' });
    }
    const lines = data.trim().split('\n');
    const records = [];
    for (let line of lines) {
      const parts = line.split('|');
      if (parts.length >= 4 && parts[0] === username) {
        const [, diagnosis, treatment, cost] = parts;
        records.push({ diagnosis, treatment, cost });
      }
    }
    res.json(records);
  });
});

app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});
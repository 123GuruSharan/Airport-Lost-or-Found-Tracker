const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const app = express();
const port = 18080;

app.use(bodyParser.json());

// Serve static files from the current directory
app.use(express.static(path.join(__dirname)));

let items = [];

app.post('/report', (req, res) => {
  const item = req.body;
  if (!item.id || !item.description) {
    return res.status(400).send('Missing required fields');
  }
  items.push(item);
  res.status(200).send('Item reported successfully');
});

app.post('/search', (req, res) => {
  const { id, description } = req.body;
  let results = [];
  if (id) {
    results = items.filter(item => item.id == id);
  } else if (description) {
    results = items.filter(item => item.description.toLowerCase().includes(description.toLowerCase()) || (item.tags && item.tags.toLowerCase().includes(description.toLowerCase())));
  } else {
    results = items; // Return all items if no search parameters
  }
  res.json({ results });
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});

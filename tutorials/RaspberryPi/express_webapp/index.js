var express = require("express")
var fs = require("fs")
var app = express()

var records = []

// Load records from local storage
fs.readFile("records.json", function(error, data) {
    if (data != undefined) {
        records = JSON.parse(data)
        console.log(records.length + " record(s) loaded from file.")
    }
})

app.get("/log/:temperature/:humidity/:light", function (req, res) {
    console.log(req.params)
    
    // Push record to list of records
    var record = {
        temperature: req.params.temperature,
        humidity: req.params.humidity,
        light: req.params.light,
        timestamp: Date.now()
    }
    records.push(record)

    // Save list of records to local file
    fs.writeFile("records.json", JSON.stringify(records), function (err) {
        if (err) 
            return console.log(err)
        else
            console.log("Records written to local file")
      })

    res.send({
        "status": "ok",
        "count": records.length
    })
})

app.get("/show/:count", function (req, res) {
    // show recent "count" of records
    res.send({
        "records": records.slice(-req.params.count) 
    })
})

app.get("/show", function (req, res) {
    res.send({
        "records": records.slice(-3)
    })
})

app.get('/dashboard', function (req, res) {
    // Generate HTML output
    var html = '<html><head><title>Dashboard</title></head><body>'
    html += '<link rel="stylesheet" type="text/css" href="https://goo.gl/nlFFwh">'
    html += '<table cellspacing="3"><thead><tr><th>Time</th><th>Temperature</th><th>Humidity</th><th>Light</th></tr></thead><tbody>\n'
    records.slice(-20).reverse().forEach(function (record) {
      html += '<tr><td>' + new Date(record.timestamp) + '</td><td>' + record.temperature + '</td><td>' + record.humidity + '</td><td>' + record.light + '</td></tr>'
    })
    html += '</tbody></table>\n'
    html += '</body></html>\n'
    // Send response
    res.send(html)
  })

app.get("/", function(req, res) {
    res.send("Welcome! This is sample app to manage sensor data")
})

app.listen(process.env.PORT || 3000, function() {
    console.log("Example app listening on port 3000")
})
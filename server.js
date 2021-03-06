var express  = require('express');
var app      = express();
var port     = process.env.PORT || 8000;
var flash    = require('connect-flash');
var morgan       = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser   = require('body-parser');
var session      = require('express-session');

app.use(express.static(__dirname + '/views'));

// set up our express application
app.use(morgan('dev')); // log every request to the console
app.use(cookieParser()); // read cookies (needed for auth)
app.use(bodyParser.json()); // get information from html forms
app.use(bodyParser.urlencoded({ extended: true }));

app.set('view engine', 'pug');

// required for passport
app.use(session({
    secret: 'wowthisisagreatsessionsecret',
    resave: true,
    saveUninitialized: true
}));

app.listen(port);
console.log('The magic happens on port ' + port);

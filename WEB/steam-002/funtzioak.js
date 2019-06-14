// JavaScript Document
var myVar = setInterval(myTimer, 5000);
// Set the configuration for your app
    var config = {
    apiKey: "xxxxxxxxxxxxxxxxxxxxxxxxxx",
    authDomain: "steam-000000.firebaseapp.com",
    databaseURL: "https://steam-000000.firebaseio.com",
    projectId: "steam-000000",
    storageBucket: "steam-000000.appspot.com",
    messagingSenderId: "xxxxxxxxxxxxx"
  };
  firebase.initializeApp(config);

  // Get a reference to the database service
  var database = firebase.database();

  // Get element from the DOM


function myTimer() {

    // Create temperature / humidity database reference
 
    //var query = firebase.database().ref("Datuak").limitToLast(1).orderByKey();
	
	var title = 'Steam-002';
	var query = firebase.database().ref("Datuak").orderByChild("Izena").equalTo("Steam-002").limitToLast(1);
	
	var datua_humidity = "Humidity:"
	var datua_temperature = "Temperature:" 
	var Humidity_db = 0;
	var Temperature_db = 0;
	var Co2_db = 0;
	var Tvoc_db = 0;

	query.once("value")
  	.then(function(snapshot) {
		snapshot.forEach(function(childSnapshot) {
		  
			// key will be "x" the first time and "y" the second time
			var key = childSnapshot.key;
			
			// childData will be the actual contents of the child
			
			var childData = childSnapshot.val();;

			Humidity_db = childSnapshot.child("Humidity").val();
			Temperature_db = childSnapshot.child("Temperature").val();
			Co2_db = childSnapshot.child("Co2").val();
			Tvoc_db = childSnapshot.child("Tvoc").val();
			console.log("humidity: " + Humidity_db);
			console.log("temperature: " + Temperature_db);
			console.log("co2: " + Co2_db);
			console.log("tvoc: " + Tvoc_db);

			// Html orrian datuak pantailaratu
			
			document.getElementById("temperature").innerText = Temperature_db + "°C";
			document.getElementById("humidity").innerText = Humidity_db + "%";
			document.getElementById("co2").innerText = Co2_db + "ppm";
			document.getElementById("tvoc").innerText = Tvoc_db + "ppb";

		});
	});
	
	}//myTimer


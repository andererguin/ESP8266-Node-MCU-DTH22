var nire_denbora_grafikoa = setInterval(myTimer, 5000);
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
	
	var query = firebase.database().ref("Datuak").orderByChild("Izena").equalTo("Steam-001").limitToLast(30);
	

	var Humidity_array = [];
	var Temperature_array =[];
	var Co2_array = [];
	var Timestamp_array = [];

	query.once("value")
  	.then(function(snapshot) {
		snapshot.forEach(function(childSnapshot) {
		  
			// key will be "x" the first time and "y" the second time
			var key = childSnapshot.key;
			
			// childData will be the actual contents of the child
			
			var childData = childSnapshot.val();;

			Humidity_array.push(childSnapshot.child("Humidity").val());
			
			Temperature_array.push(childSnapshot.child("Temperature").val());
			
			Co2_array.push(childSnapshot.child("Co2").val());
			
			Timestamp_array.push(childSnapshot.child("Timestamp").val());
						
			
		});
				
	});




function myTimer() {  //Errepikatu grakikoaren karga 20 segunduro

clearTimeout(nire_denbora_grafikoa);
	
var lineChartData = {
			labels: Timestamp_array,
			datasets: [{
				label: 'Co2 - ppm',
				borderColor: window.chartColors.red,
				backgroundColor: window.chartColors.red,
				fill: false,
				data: Co2_array,
				yAxisID: 'y-axis-1',
			}, {
				label: 'Tenperatura - Cº',
				borderColor: window.chartColors.blue,
				backgroundColor: window.chartColors.blue,
				fill: false,
				data: Temperature_array,
				yAxisID: 'y-axis-2'
			}, {
				label: 'Hezetasuna',
				borderColor: window.chartColors.purple,
				backgroundColor: window.chartColors.purple,
				fill: false,
				data: Humidity_array,
				yAxisID: 'y-axis-2'
			}]
		};
	
		
	
	
	
		var ctx = document.getElementById('canvas').getContext('2d');
			window.myLine = Chart.Line(ctx, {
				data: lineChartData,
				options: {
					responsive: true,
					hoverMode: 'index',
					stacked: false,
					title: {
						display: true,
						text: ''
					},
					scales: {
						yAxes: [{
							type: 'linear', // only linear but allow scale type registration. This allows extensions to exist solely for log scale for instance
							display: true,
							position: 'left',
							id: 'y-axis-1',
						}, {
							type: 'linear', // only linear but allow scale type registration. This allows extensions to exist solely for log scale for instance
							display: true,
							position: 'right',
							id: 'y-axis-2',

							// grid line settings
							gridLines: {
								drawOnChartArea: false, // only want the grid lines for one axis to show up
							},
						}, {
							type: 'linear', // only linear but allow scale type registration. This allows extensions to exist solely for log scale for instance
							display: false,
							position: 'right',
							id: 'y-axis-3',

							// grid line settings
							gridLines: {
								drawOnChartArea: false, // only want the grid lines for one axis to show up
							},
						}],
					}
				}
			});
	
}//myTimer

//Put Server URL Here
var api_base_url = "http://.../..../api/";

var chart0;
var chart1;
var unit = "";

document.addEventListener("DOMContentLoaded", (event) => {
	setupDownloadButton();
	createCharts();
	updateData();
	setInterval(updateData, 30000);
});


var getJSON = function(url, callback) {
	var xhr = new XMLHttpRequest();
	xhr.open('GET', url, true);
	xhr.responseType = 'json';
	xhr.onload = function() {
		var status = xhr.status;
		if (status === 200) {
			callback(null, xhr.response);
		} else {
			callback(status, xhr.response);
		}
	};
	xhr.send();
};

function setupDownloadButton(){
	document.getElementById('btn-download').addEventListener("click", function(){
		window.location.href = api_base_url+"export/";
	}); 
}

function updateData(){
	
	getJSON(api_base_url+"get/",
			function(err, data) {
		if (err !== null) {
			alert('ERROR: ' + err);
		} else {
			
			if(!data.header.backend_version.startsWith("1.")){
				alert("Incompatible API version detected!");
				return;
			}
			
			
			unit = data.header.target_unit;
			
			var factor = data.header.target_unit_factor;
			
			chart0.data.datasets[0].data = [];
			chart0.data.labels = [];
			
			for (var[hour, hour_data] of Object.entries(data.hours)){
							chart0.data.labels.push(hour);
							chart0.data.datasets[0].data.push((hour_data.consumption*factor).toFixed(1));
					}
			
			chart0.update();
			
			
			chart1.data.datasets[0].data = [];
			chart1.data.labels = [];
			
			for (var[day, day_data] of Object.entries(data.days)){
							chart1.data.labels.push(day);
							chart1.data.datasets[0].data.push((day_data.consumption*factor).toFixed(0));
					}
			
			chart1.update();
			
		}
			
	});


}



function createCharts(){
	
	var ctx = document.getElementById('chart-0');
	if (ctx) {
		chart0 = new Chart(ctx.getContext('2d'), {
			type: 'line',
			data: {
				labels: [],
				datasets: [
					{
						label: 'Consumption',
						data: [],
						borderColor: ['#ff9671FF'],
						borderWidth: 2
					}
				]
			},
			options: {
				animation: {
					duration: 2000
				},
				scales: {
					y: {
						border: {
          					display: true,
         					color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
        				},
						grid: {
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
						},
						ticks: {
							maxTicksLimit: 6,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
							callback: function(value, index, ticks) {
								return value + unit;
							}
						},
						suggestedMax: 1,
						suggestedMin: 0,
					},
					x: {
						border: {
          					display: true,
         					color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
        				},
						grid: {
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
						},
						ticks: {
							maxTicksLimit: 6,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
						},
					}	
				},
				elements: {
					point: {
						radius: 4,
						hitRadius: 20
					}
				},
				plugins: {
					legend: {
						position: 'top',
						align: 'end',
						labels: {
							boxWidth: 6,
							boxHeight: 6,
							usePointStyle: true,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
							font: {
								size: 12,
								weight: 'bold',
							}
						}
					},
					tooltip: {
						displayColors: false
					}	
				},
				tooltips: {
					mode: 'index',
					intersect: false
				},
				hover: {
					mode: 'nearest',
					intersect: true
				}
			}
		});
	}


	var ctx = document.getElementById('chart-1');
	if (ctx) {
		chart1 = new Chart(ctx.getContext('2d'), {
			type: 'bar',
			data: {
				labels: [],
				datasets: [
					{
						label: 'Consumption',
						data: [],
						backgroundColor: ['rgba(121, 231, 251, 0.3)'],
						borderColor: ['#77e8fb'],
						borderWidth: 2
					}
				]
			},
			options: {
				animation: {
					duration: 2000
				},
				scales: {
					y: {
						border: {
          					display: true,
         					color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
        				},
						grid: {
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
						},
						ticks: {
							maxTicksLimit: 6,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
							callback: function(value, index, ticks) {
								return value + unit;
							}
						},
						suggestedMax: 1,
						suggestedMin: 0,
					},
					x: {
						border: {
          					display: true,
         					color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
        				},
						grid: {
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-line")
						},
						ticks: {
							maxTicksLimit: 6,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
						},
					}	
				},
				plugins: {
					legend: {
						position: 'top',
						align: 'end',
						labels: {
							boxWidth: 6,
							boxHeight: 6,
							usePointStyle: true,
							color: getComputedStyle(ctx).getPropertyValue("--color-chart-font"),
							font: {
								size: 12,
								weight: 'bold',
							}
						}
					},
					tooltip: {
						displayColors: false
					}	
				},
				tooltips: {
					mode: 'index',
					intersect: false
				},
				hover: {
					mode: 'nearest',
					intersect: true
				}
			}
		});
	}

	
	
}


// On profite du chargement du script pour mettre à jour l'heure du serveur
fetch('time', {method: "PUT", body: Date.now()})
    .catch(e => console.log("Error while setting up time " + e));

function onButton() {
    fetch('valvik/on', {method: "POST"})
    .catch(e => console.log("Error while turning valvik on " + e));
}

function offButton() {
    fetch('valvik/off', {method: "POST"})
    .catch(e => console.log("Error while turning valvik of " + e));
}

function getHistory() {
    fetch("valvik/history")
    .then(response => response.json())
    .then(data => {showStats(data); });
}

var chart;

function showStats(histo) {
    const data_stats = histo.flatMap(item => {
        const date1 = new Date(item.start).toLocaleString();
        const date2 = new Date(item.end).toLocaleString();
        var data1 = {"x" : date1, "y" : false};
        var data2 = {"x" : date1, "y" : true};
        var data3 = {"x" : date2, "y" : true};
        var data4 = {"x" : date2, "y" : false};
        return [data1, data2, data3, data4];
    });

    console.log("chart = " + chart);
    if(chart == undefined) {
        const data = {
            datasets: [{
                label: 'Arrosage',
                backgroundColor: 'rgba(44, 130, 201, 1)',
                borderColor: 'rgba(44, 130, 201, 1)',
                data: data_stats
            }]
        };
        const config = {
            type: 'line',
            data,
            options: {}
        };
        chart = new Chart(document.getElementById('arrosage'), config);
    }
    else {
        chart.data.datasets[0].data = data_stats; 
        chart.update();
    }
}

function getSettings() {
    fetch("settings")
    .then(response => response.json())
    .then(data => {showSettings(data); });
}

function showSettings(settings) {
    document.getElementById('timestamp').innerText = new Date(settings.timestamp).toLocaleString();
}

function openTab(tabId) {
    var i;
    var x = document.getElementsByClassName("tab");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(tabId).style.display = "block";
}


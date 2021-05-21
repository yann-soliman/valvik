// On profite du chargement du script pour mettre à jour l'heure du serveur
refreshTime();

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

function getTime() {
    fetch("time")
    .then(response => response.json())
    .then(data => {showStats(data); });
}

function refreshTime() {
    const timestamp = Date.now();
    fetch('time', {method: "PUT", body: timestamp})
    .then(_ => showTime(timestamp))
    .catch(e => console.log("Error while setting up time " + e));
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
    .then(data => {refreshSettings(data); });
}

function refreshSettings(settings) {
    showTime(settings.timestamp);
    document.getElementById("humiditySensorCheckBox").checked = settings.shouldUseHumiditySensor ;
    document.getElementById("programmableWateringCheckbox").checked = settings.shouldUseProgrammableWatering ;
}

function showTime(timestamp) {
    const date = new Date(timestamp);
    document.getElementById('timestamp').innerText = date.toLocaleDateString() + " " + date.toLocaleTimeString();
}

function toggleHumiditySensor() {
    fetch("settings/sensor/humidity/toggle", {method: "PUT"})
    .catch(e => console.log("Error while toggling humidity sensor " + e));
}

function toggleProgrammableWatering() {
    fetch("settings/programmable-watering/toggle", {method: "PUT"})
    .catch(e => console.log("Error while toggling programmable watering " + e));
}

function openTab(tabId) {
    var i;
    var x = document.getElementsByClassName("tab");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(tabId).style.display = "block";
}


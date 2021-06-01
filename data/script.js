// On profite du chargement du script pour mettre à jour l'heure du serveur
refreshTime();


function showManual() {
    getWateringState();
    getMoistureSensorState();    
}

function getWateringState() {
    fetch('valvik/state')
    .then(response => response.text())
    .then(wateringState => showWateringState(parseInt(wateringState)))
    .catch(e => showError("Error while getting valvik status " + e));
}

function showWateringState(wateringState) {
    document.getElementById("watering-state").checked = wateringState;
}

function getMoistureSensorState() {
    fetch("sensor/moisture/state")
    .then(response => response.text())
    .then(moistureState => showMoistureSensor(parseInt(moistureState)))
    .catch(e => showError("Error while getting valvik status " + e));
}

function showMoistureSensor(moistureState) {
    const moistureStateElement = document.getElementById("moisture-state");
    if(!moistureState) {
        moistureStateElement.src = "cactus.png";
    }
    else {
        moistureStateElement.src = "plant.png";
    }
}

function toggleWatering() {
    const minutes = parseInt(document.getElementById("manual-watering-minutes").value);
    const seconds = parseInt(document.getElementById("manual-watering-seconds").value);
    fetch('valvik/toggle', {method: "POST", body: JSON.stringify({"minutes": minutes, "seconds": seconds})})
    .catch(e => showError("Error while toggling valvik " + e));
}

function getHistory() {
    fetch("valvik/history")
    .then(response => response.json())
    .then(data => showStats(data))
    .catch(e => showError("Error while toggling valvik " + e));
}

function resetHistory() {
    fetch("valvik/history", {method: "DELETE"})
    .catch(e => showError("Error while resetting history " + e));
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
    .catch(e => showError("Error while setting up time " + e));
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
    document.getElementById("moisture-sensor-checkbox").checked = settings.shouldUseMoistureSensor ;
    document.getElementById("programmable-watering-checkbox").checked = settings.shouldUseProgrammableWatering ;
    document.getElementById("current-moisture-sensor-percentage").innerHTML = settings.currentMoistureSensorPercentage;
    document.getElementById("moisture-sensor-threshold-range").value = settings.moistureSensorThreshold;
    document.getElementById("moisture-sensor-threshold-value").innerHTML = settings.moistureSensorThreshold;
}

function showTime(timestamp) {
    const date = new Date(timestamp);
    document.getElementById('timestamp').innerText = date.toLocaleDateString() + " " + date.toLocaleTimeString();
}

function toggleMoistureSensor() {
    fetch("settings/sensor/moisture/toggle", {method: "PUT"})
    .catch(e => showError("Error while toggling moisture sensor " + e));
}

function toggleProgrammableWatering() {
    fetch("settings/programmable-watering/toggle", {method: "PUT"})
    .catch(e => showError("Error while toggling programmable watering " + e));
}

var updateMoistureSensorThresholdTimeout;
function updateMoistureSensorThreshold() {
    const threshold = document.getElementById("moisture-sensor-threshold-range").value;
    document.getElementById("moisture-sensor-threshold-value").innerHTML = threshold;
    clearTimeout(updateMoistureSensorThresholdTimeout);
    updateMoistureSensorThresholdTimeout = setTimeout(
        () => fetch("settings/sensor/moisture/threshold", {method: "PUT", body: threshold})
        .catch(e => showError("Error while settings moisture sensor percentage" + e))
        , 500);
}

function openTab(tabId) {
    var i;
    var x = document.getElementsByClassName("tab");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(tabId).style.display = "block";
}

function showError(error) {
    document.getElementById("text-error").innerText = error;
    document.getElementById('error-modal').style.display="block";
}

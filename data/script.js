function onButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "valvik/on");
    xhttp.send();
}

function offButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("POST", "valvik/off");
    xhttp.send();
}

function setTime() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("PUT", "time");
    xhttp.send(document.getElementById("datetime").valueAsNumber);
}

function getHistory() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "valvik/history");
    xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200)
        {
            showStats(JSON.parse(this.responseText));
        }
    };
    xhttp.send(document.getElementById("datetime").valueAsNumber);
}

function showStats(histo) {
    const data1 = histo.flatMap(item => {
        const date1 = new Date(item.start).toLocaleString();
        const date2 = new Date(item.end).toLocaleString();
        var data1 = {"x" : date1, "y" : false};
        var data2 = {"x" : date1, "y" : true};
        var data3 = {"x" : date2, "y" : true};
        var data4 = {"x" : date2, "y" : false};
        return [data1, data2, data3, data4]
    })
    const data = {
        datasets: [{
            label: 'Arrosage',
            backgroundColor: 'rgba(44, 130, 201, 1)',
            borderColor: 'rgba(44, 130, 201, 1)',
            data: data1
        }]
    };
    const config = {
        type: 'line',
        data,
        options: {}
    };
    var myChart = new Chart(
        document.getElementById('arrosage'),
        config
        );
    }
    
function openTab(tabId) {
    var i;
    var x = document.getElementsByClassName("tab");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    document.getElementById(tabId).style.display = "block";
}
    
    
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
            document.getElementById("histories").innerHTML = this.responseText;
        }
    };
    xhttp.send(document.getElementById("datetime").valueAsNumber);
}

function openTab(tabId) {
    var i;
    var x = document.getElementsByClassName("tab");
    for (i = 0; i < x.length; i++) {
      x[i].style.display = "none";
    }
    document.getElementById(tabId).style.display = "block";
}

// setInterval(function getData()
// {
//     var xhttp = new XMLHttpRequest();

//     xhttp.onreadystatechange = function()
//     {
//         if(this.readyState == 4 && this.status == 200)
//         {
//             document.getElementById("valeurLuminosite").innerHTML = this.responseText;
//         }
//     };

//     xhttp.open("GET", "lireLuminosite", true);
//     xhttp.send();
// }, 2000);


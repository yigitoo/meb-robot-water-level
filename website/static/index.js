const background = document.querySelector("#background");
const valveState = document.querySelector("#valveState");
const liquidLevel = document.querySelector("#liquidLevel");

function getData() {
  // 1. Create a new XMLHttpRequest object
  let xhr = new XMLHttpRequest();
  xhr.responseType = "json";

  // 2. Configure it: GET-request for the URL /getData
  xhr.open("GET", "http://localhost:8080/getData");

  // 3. Send the request over the network
  xhr.send();

  // 4. This will be called after the response is received
  xhr.onload = function () {
    if (xhr.status == 200) {
      let response = xhr.response;

      if (response.state === "open") {
        background.style.backgroundColor = "green";
        valveState.textContent = "MUSLUK: AÇIK";
      } else {
        background.style.backgroundColor = "red";
        valveState.textContent = "MUSLUK: KAPALI";
      }
      if (response.level === 1023) {
        liquidLevel.textContent = `SEVİYE: 1024/1024 (TAM DOLU)`;
      } else {
        liquidLevel.textContent = `SEVİYE: ${response.level}/1024`;
      }
    } else {
      alert(`Error ${xhr.status}: ${xhr.statusText}`); // e.g. 404: Not Found
    }
  };

  xhr.onprogress = function (event) {
    if (event.lengthComputable) {
    } else {
      alert("Request failed");
    }
  };

  xhr.onerror = function () {
    alert("Request failed");
  };
}

setInterval(getData, 1000);

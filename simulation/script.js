const intervalTime = 6000;
const yellowTimeout = intervalTime - 3000;
const yellowDuration = 1200;
var amb = 0;
var myInterval, timeout1, timeout2;
var currentState;

function stateA(){
    currentState = 'A';
    document.getElementById("A1").classList.remove("red"); 
    document.getElementById("A3").classList.add("green");
    document.getElementById("B1").classList.add("red");
    document.getElementById("C1").classList.add("red");
    document.getElementById("D1").classList.add("red");

    timeout1=setTimeout(() => {
        document.getElementById("A3").classList.remove("green");
        document.getElementById("A2").classList.add("yellow");
        timeout2=setTimeout(() => {
            document.getElementById("A2").classList.remove("yellow");
            document.getElementById("A1").classList.add("red"); 
            
        }, yellowDuration);
    }, yellowTimeout);


}

function stateB(){
    currentState = 'B';
    document.getElementById("B1").classList.remove("red"); 
    document.getElementById("B3").classList.add("green");
    document.getElementById("A1").classList.add("red");
    document.getElementById("C1").classList.add("red");
    document.getElementById("D1").classList.add("red");

    timeout1=setTimeout(() => {
        document.getElementById("B3").classList.remove("green");
        document.getElementById("B2").classList.add("yellow");
        timeout2=setTimeout(() => {
            document.getElementById("B2").classList.remove("yellow");
            document.getElementById("B1").classList.add("red"); 
        }, yellowDuration);
    }, yellowTimeout);

}

function stateC(){
    currentState = 'C';
    document.getElementById("C1").classList.remove("red"); 
    document.getElementById("C3").classList.add("green");
    document.getElementById("A1").classList.add("red");
    document.getElementById("B1").classList.add("red");
    document.getElementById("D1").classList.add("red");

    timeout1=setTimeout(() => {
        document.getElementById("C3").classList.remove("green");
        document.getElementById("C2").classList.add("yellow");
        timeout2=setTimeout(() => {
            document.getElementById("C2").classList.remove("yellow");
            document.getElementById("C1").classList.add("red"); 
        }, yellowDuration);
    }, yellowTimeout);

}
function stateD(){
    currentState = 'D';
    document.getElementById("D1").classList.remove("red"); 
    document.getElementById("D3").classList.add("green");
    document.getElementById("A1").classList.add("red");
    document.getElementById("B1").classList.add("red");
    document.getElementById("C1").classList.add("red");

    timeout1=setTimeout(() => {
        document.getElementById("D3").classList.remove("green");
        document.getElementById("D2").classList.add("yellow");
        timeout2=setTimeout(() => {
            document.getElementById("D2").classList.remove("yellow");
            document.getElementById("D1").classList.add("red"); 
        }, yellowDuration);
    }, yellowTimeout);

}

const states = [stateA, stateB, stateD, stateC ];
let index = 0;

function callNextState() {
    states[index]();
    index = (index + 1) % states.length; 
}
          
function startAmbulance(start){
    clearInterval(myInterval);
    clearTimeout(timeout1);
    clearTimeout(timeout2);

    amb = 1;
    

    ['A', 'B', 'C', 'D'].forEach(signal => {
        for (let i = 1; i <= 3; i++) {
            document.getElementById(`${signal}${i}`).classList.remove("red", "green", "yellow");
        }
      });

      ['A', 'B', 'C', 'D'].forEach(signal => {
            document.getElementById(`${signal}${2}`).classList.add("yellow");
    
      });

        setTimeout(() => {
        ['A', 'B', 'C', 'D'].forEach(signal => {
                document.getElementById(`${signal}${2}`).classList.remove("yellow");
          });

            ['A', 'B', 'C', 'D'].forEach(signal => {
                if(signal != start){
                    document.getElementById(`${signal}${1}`).classList.add("red");
                }
                document.getElementById(`${start}${3}`).classList.add("green");
    
          });
        }, 1000);

    
}

function endAmbulance(){
    if(!amb){
        return;
    }
    amb = 0;
    ['A', 'B', 'C', 'D'].forEach(signal => {
        for (let i = 1; i <= 3; i++) {
            document.getElementById(`${signal}${i}`).classList.remove("red", "green", "yellow");
        }
      });

    switch(currentState){
        case 'A':
            index = 0;
            break;
        case 'B':
            index = 1;
            break;
        case 'C':
            index = 3;
            break;
        case 'D':
            index = 2;
            break;
    }
    callNextState();
    myInterval = setInterval(callNextState, intervalTime);
}

document.getElementById("playBtn").addEventListener("click", () => {
    if(amb == 0){
        amb = 0;
        callNextState();
        myInterval = setInterval(callNextState, intervalTime);
        
    }
    else{
        endAmbulance();
    }
})


const movingImage = document.getElementById('moving-image');
function moveImage() {
  setTimeout(() => {
    const screenWidth = window.innerWidth;
    const imageWidth = movingImage.clientWidth;
    const finalPosition = screenWidth - imageWidth;
  
    movingImage.style.left = finalPosition + 'px';
    setTimeout(() => {
        endAmbulance();
    }, 4000);
  }, 500);
 
}
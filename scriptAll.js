bec_coord3 = [
    {
        "bec51": [3537,1491],
        "bec52": [3537,614],
        "bec53": [2662,614],
        "bec54": [1987,614],
        "bec55": [1987,1491],
        "bec56": [2662,1491],

    }
]

bec_coord4 = [
    {
        "bec71": [1232,601],
        "bec72": [1030,601],
        "bec73": [827,601],
        "bec74": [1232,331],
        "bec75": [1030,331],
        "bec76": [827,331],
        "bec77": [1232,156],
        "bec78": [1030,156],
        "bec79": [827,156],
    }
]




const api_url3 = ''; // input your api url here

async function getDataAll_room(){
    
        var ctx = document.getElementById('canvasAll').getContext('2d');

        const response = await fetch(api_url3);
        const data = await response.json();
        var last = data.length - 1;
        var bec_array = data[last]['value']['workingbec']['becname'] ;
        var bec_pos = [parseFloat(data[last]['xyposition']['xpos']), parseFloat(data[last]['xyposition']['ypos'])];
        var cov_pos = [3537 - bec_pos[1]*135, 1491 - bec_pos[0]*134.84];
        // console.log(bec_array, bec_pos);

        for(i=0; i<=bec_array.length-1; i++){
            ctx.fillStyle = "#20ab20";  
            ctx.beginPath();
            ctx.arc(bec_coord3[0][bec_array[i]][0],bec_coord3[0][bec_array[i]][1],21,0,Math.PI * 2);
            ctx.fill();
        }

        ctx.fillStyle = "red";  // draw a red circle 100 display pixels in size.
        ctx.beginPath();
        ctx.arc(cov_pos[0],cov_pos[1],12,0,Math.PI * 2);
        ctx.fill();
        ctx.fillStyle = "black";
        ctx.font = "40px Arial";
        ctx.fillText("(x: "+Number(bec_pos[0]).toFixed(2)+" m, y: "+Number(bec_pos[1]).toFixed(2)+" m)",cov_pos[0]+15,cov_pos[1]-15);
        
}
const api_url4 = ''; // input your api url here 

async function getDataAll_factory(){
    
        var ctx = document.getElementById('canvasAll').getContext('2d');

        const response = await fetch(api_url4);
        const data = await response.json();
        var last = data.length - 1;
        var bec_array = data[last]['value']['workingbec']['becname'] ;
        var bec_pos = [parseFloat(data[last]['xyposition']['xpos']), parseFloat(data[last]['xyposition']['ypos'])];
        var cov_pos = [692+bec_pos[0]*135, 694 - bec_pos[1]*134.84];
        // console.log(bec_array, bec_pos);

        for(i=0; i<=bec_array.length-1; i++){
            ctx.fillStyle = "#20ab20";  
            ctx.beginPath();
            ctx.arc(bec_coord4[0][bec_array[i]][0],bec_coord4[0][bec_array[i]][1],21,0,Math.PI * 2);
            ctx.fill();
        }

        ctx.fillStyle = "red";  // draw a red circle 100 display pixels in size.
        ctx.beginPath();
        ctx.arc(cov_pos[0],cov_pos[1],12,0,Math.PI * 2);
        ctx.fill();
        ctx.fillStyle = "black";
        ctx.font = "40px Arial";
        ctx.fillText("(x: "+Number(bec_pos[0]).toFixed(2)+" m, y: "+Number(bec_pos[1]).toFixed(2)+" m)",cov_pos[0]+15,cov_pos[1]-15);
        
}



function draw3() {
    var ctx = document.getElementById('canvasAll').getContext('2d');
    var img = new Image();
    img.src = './images/layout.png';
    img.onload = function(){

        canvasAll.width =  3600;
        canvasAll.height = 1550;
        // set the display size
        canvasAll.style.width =  "1335px";
        canvasAll.style.height = "575px";
        ctx.drawImage(img, 0, 0, img.width,    img.height,     // source rectangle
            0, 0, canvasAll.width, canvasAll.height); // destination rectangle
        

        ctx.fillStyle = "black";  
        ctx.beginPath();
        ctx.arc(692,694,10,0,Math.PI * 2);
        ctx.fill();
        ctx.fillStyle = "black";
        ctx.font = "30px Arial";
        ctx.fillText("(0, 0)", 654,745);
        
        //bec73
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(827,601,21,0,Math.PI * 2);
        ctx.fill();
        
        //bec72
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1030,601,21,0,Math.PI * 2);
        ctx.fill();

        //bec71
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1232,601,21,0,Math.PI * 2);
        ctx.fill();

        //bec76
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(827,331,21,0,Math.PI * 2);
        ctx.fill();

        //bec75
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1030,331,21,0,Math.PI * 2);
        ctx.fill();

        //bec74
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1232,331,21,0,Math.PI * 2);
        ctx.fill();

        //bec79
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(827,156,21,0,Math.PI * 2);
        ctx.fill();

        //bec78
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1030,156,21,0,Math.PI * 2);
        ctx.fill();
        
        //bec77
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1232,156,21,0,Math.PI * 2);
        ctx.fill();    

        //bec51
        ctx.fillStyle = "grey"; 
        ctx.beginPath();
        ctx.arc(3537,1491,21,0,Math.PI * 2);
        ctx.fill();
        
        //bec52
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(3537,614,21,0,Math.PI * 2);
        ctx.fill();

        //bec56
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(2662,1491,21,0,Math.PI * 2);
        ctx.fill();

        //bec53
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(2662,614,21,0,Math.PI * 2);
        ctx.fill();

        //bec55
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1987,1491,21,0,Math.PI * 2);
        ctx.fill();

        //bec54
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1987,614,21,0,Math.PI * 2);
        ctx.fill();

    };
    
    
}
draw3();
getDataAll_room();
setInterval(getDataAll_factory, 500);



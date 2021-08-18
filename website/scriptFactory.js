bec_coord = [
    {
        "bec71": [1532, 761],
        "bec72": [1280, 761],
        "bec73": [1028, 761],
        "bec74": [1532, 418],
        "bec75": [1280, 418],
        "bec76": [1028, 418],
        "bec77": [1532, 196],
        "bec78": [1280, 196],
        "bec79": [1028, 196],

    }
]

const api_url = ''; // input your api url

async function getData(){
    
        var ctx = document.getElementById('canvas').getContext('2d');

        const response = await fetch(api_url);
        const data = await response.json();
        var last = data.length - 1;
        var bec_array = data[last]['value']['workingbec']['becname'] ;
        var bec_pos = [parseFloat(data[last]['xyposition']['xpos']), parseFloat(data[last]['xyposition']['ypos'])];
        var cov_pos = [860+bec_pos[0]*168, 875 - bec_pos[1]*171.5];
        // console.log(bec_array, bec_pos, cov_pos);

        for(i=0; i<=bec_array.length-1; i++){
            ctx.fillStyle = "#20ab20";  
            ctx.beginPath();
            ctx.arc(bec_coord[0][bec_array[i]][0],bec_coord[0][bec_array[i]][1],27,0,Math.PI * 2);
            ctx.fill();
        }

        ctx.fillStyle = "red";  
        ctx.beginPath();
        ctx.arc(cov_pos[0],cov_pos[1],12,0,Math.PI * 2);
        ctx.fill();
        
}

async function get_route_Data(){

    try {
        var ctx = document.getElementById('canvas').getContext('2d');

        const response = await fetch(api_url);
        const data = await response.json();
        // console.log(data)

        var last = data.length - 1;
        for(i=0; i<=last; i++){
            // var bec_array = data[i]['value']['workingbec']['becname'] ;
            var bec_pos = [parseFloat(data[i]['xyposition']['xpos']), parseFloat(data[i]['xyposition']['ypos'])];
            var cov_pos = [860+bec_pos[0]*168, 875 - bec_pos[1]*171.5];

            ctx.fillStyle = "red";  
            ctx.beginPath();
            ctx.arc(cov_pos[0],cov_pos[1],12,0,Math.PI * 2);
            ctx.fill();
        }
    }
    catch (e) {
        console.log(e)
    }  
}


function draw() {
    var ctx = document.getElementById('canvas').getContext('2d');
    var img = new Image();
    img.src = './images/factory.png';
    img.onload = function(){

        canvas.width = canvas.height = 1800;
        // set the display size
        canvas.style.width =  "537px";
        canvas.style.height = "528px";
        ctx.drawImage(img, 0, 0, img.width,    img.height,     // source rectangle
            0, 0, canvas.width, canvas.height); // destination rectangle
        
        ctx.fillStyle = "black";  
        ctx.beginPath();
        ctx.arc(860,875,15,0,Math.PI * 2);
        ctx.fill();
        ctx.fillStyle = "black";
        ctx.font = "48px Arial";
        ctx.fillText("(0, 0)", 805,935);
        
        //bec73
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1028,761,27,0,Math.PI * 2);
        ctx.fill();
        
        //bec72
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1280,761,27,0,Math.PI * 2);
        ctx.fill();

        //bec71
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1532,761,27,0,Math.PI * 2);
        ctx.fill();

        //bec76
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1028,418,27,0,Math.PI * 2);
        ctx.fill();

        //bec75
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1280,418,27,0,Math.PI * 2);
        ctx.fill();

        //bec74
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1532,418,27,0,Math.PI * 2);
        ctx.fill();

        //bec79
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1028,196,27,0,Math.PI * 2);
        ctx.fill();

        //bec78
        ctx.fillStyle = "grey"; 
        ctx.beginPath();
        ctx.arc(1280,196,27,0,Math.PI * 2);
        ctx.fill();
        
        //bec77
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1532,196,27,0,Math.PI * 2);
        ctx.fill();


    };
    
    
}
draw();
getData();
document.getElementById("routebutton").onclick = function() { 
    draw();
    get_route_Data() };
document.getElementById("locatebutton").onclick = function() { 
    draw();
    getData() };


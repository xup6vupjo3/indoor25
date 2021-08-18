bec_coord2 = [
    {
        "bec51": [1732,993],
        "bec52": [1732,66],
        "bec53": [804,66],
        "bec54": [89,66],
        "bec55": [89,993],
        "bec56": [804,993],

    }
]

const api_url2 = ''; //input your api url

async function getDataRoom(){
    
        var ctx = document.getElementById('canvasRoom').getContext('2d');

        const response = await fetch(api_url2);
        const data = await response.json();
        var last = data.length - 1;
        var bec_array = data[last]['value']['workingbec']['becname'] ;
        var bec_pos = [parseFloat(data[last]['xyposition']['xpos']), parseFloat(data[last]['xyposition']['ypos'])];
        var cov_pos = [1732 - bec_pos[1]*142.87, 993 - bec_pos[0]*142.62];
        // console.log(bec_array, bec_pos);

        for(i=0; i<=bec_array.length-1; i++){
            ctx.fillStyle = "#20ab20";  
            ctx.beginPath();
            ctx.arc(bec_coord2[0][bec_array[i]][0],bec_coord2[0][bec_array[i]][1],22,0,Math.PI * 2);
            ctx.fill();
        }

        ctx.fillStyle = "red";  
        ctx.beginPath();
        ctx.arc(cov_pos[0],cov_pos[1],12,0,Math.PI * 2);
        ctx.fill();
        
}

async function get_route_RoomData(){

    try {
        var ctx = document.getElementById('canvasRoom').getContext('2d');

        const response = await fetch(api_url2);
        const data = await response.json();
        // console.log(data)

        var last = data.length - 1;
        for(i=0; i<=last; i++){
            // var bec_array = data[i]['value']['workingbec']['becname'] ;
            var bec_pos = [parseFloat(data[i]['xyposition']['xpos']), parseFloat(data[i]['xyposition']['ypos'])];
            var cov_pos = [1732 - bec_pos[1]*142.87, 993 - bec_pos[0]*142.62];

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


function draw2() {
    var ctx = document.getElementById('canvasRoom').getContext('2d');
    var img = new Image();
    img.src = './images/classroom.png';
    img.onload = function(){

        canvasRoom.width =  1800;
        canvasRoom.height = 1059;
        // set the display size
        canvasRoom.style.width =  "630px";
        canvasRoom.style.height = "371.5px";
        ctx.drawImage(img, 0, 0, img.width,    img.height,     // source rectangle
            0, 0, canvasRoom.width, canvasRoom.height); // destination rectangle
        
        //bec51
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1732,993,22,0,Math.PI * 2);
        ctx.fill();
        
        //bec52
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(1732,66,22,0,Math.PI * 2);
        ctx.fill();

        //bec56
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(804,993,22,0,Math.PI * 2);
        ctx.fill();

        //bec53
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(804,66,22,0,Math.PI * 2);
        ctx.fill();

        //bec55
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(89,993,22,0,Math.PI * 2);
        ctx.fill();

        //bec54
        ctx.fillStyle = "grey";  
        ctx.beginPath();
        ctx.arc(89,66,22,0,Math.PI * 2);
        ctx.fill();

    };
    
    
}
draw2();
getDataRoom();
document.getElementById("routebuttonRoom").onclick = function() { 
    draw2();
    get_route_RoomData() };
document.getElementById("locatebuttonRoom").onclick = function() { 
    draw2();
    getDataRoom() };


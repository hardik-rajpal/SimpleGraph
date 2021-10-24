
const setBackground = (url, canvas)=>{
    bgimg = fabric.Image.fromURL('sky.jpg', img=>{
        canvas.backgroundImage = img
        canvas.renderAll();
    })
    
    canvas.renderAll()
}
const initCanvas = (id)=>{
    return new fabric.Canvas(id, {
        width:500,
        height:500
    })
}
const canvas = initCanvas("canvas");
setBackground('sky.jpg', canvas)
// canvas.on('mouse:move', (e)=>{
//     console.log(e)
// })
c = new fabric.Circle({
    left:100,
    top:100,
    strokeWidth:5,
    radius:12,
    fill:'#fff',
    stroke:'#666'
});
canvas.add()
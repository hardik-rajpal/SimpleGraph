let radius = 15;
let radroot = Math.SQRT1_2*radius;
V = {}
E = {}
data = { "H":"0",
"V": [
{ "ptr" : "0xf91a58",
"color" : "red",
"label" : "1",
"weight": 1,
"coords": {
"x": 0,
"y": 0
},
"outlist" : [
{ 
"ptr" : "0xf91998",
"end" : "0xf91ab8",
"conjugate" : "0xf97850",
"weight" : 16325520,
"color" : "",
"label" : "a"
},
{ 
"ptr" : "0xf97898",
"end" : "0xf91b18",
"conjugate" : "0xf978e0",
"weight" : 16325536,
"color" : "",
"label" : "a"
}

]
},
{ "ptr" : "0xf91ab8",
"color" : "red",
"label" : "2",
"weight": 1,
"coords": {
"x": 0,
"y": 0
},
"outlist" : [
{ 
"ptr" : "0xf97850",
"end" : "0xf91a58",
"conjugate" : "0xf91998",
"weight" : 16325520,
"color" : "",
"label" : "a"
}

]
},
{ "ptr" : "0xf91b18",
"color" : "red",
"label" : "3",
"weight": 1,
"coords": {
"x": 0,
"y": 0
},
"outlist" : [
{ 
"ptr" : "0xf978e0",
"end" : "0xf91a58",
"conjugate" : "0xf97898",
"weight" : 16325536,
"color" : "",
"label" : "a"
}

]
}
]

}

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
        height:500,
        backgroundColor:'#eef'
    })
}
const canvas = initCanvas("canvas");
class VNode{
    constructor(x, y, label, color,canvas){
        this.x = x
        this.y = y
        this.shape = new fabric.Circle({
            left:x,
            top:(canvas.height - y),
            strokeWidth:5,
            radius:radius,
            fill:color,
            stroke:'#666',
        })
        this.text = new fabric.Text(label, {
            left:x +radroot,
            top:(canvas.height - y+radroot/2),
            fontSize:20
        })
        this.group = new fabric.Group([this.shape, this.text])
        this.group.hasControls = false;
        this.group.edges=[]
        this.group.edges2=[]
        canvas.add(this.group)
    }
}
class Edge{
    constructor(n1, n2, label, color,canvas){
        this.n1 = n1
        this.n2 = n2
        this.label = label
        // this.text = new fabric.Text(label,{
        //     fontSize:20
        // })
        this.line = new fabric.Line([n1.group.left + radroot, n1.group.top + radroot, n2.group.left+radroot, n2.group.top + radroot],{
            fill:color,
            stroke:color,
            strokeWidth:5,
            evented:false,
            selectable:false
        })
        // canvas.add(this.line)
        // this.group = new fabric.Group([this.text, this.line])
        canvas.add(this.line)
        canvas.sendToBack(this.line)
        n1.group.edges.push(this.line)
        n2.group.edges2.push(this.line)
        // console.log(n1.group.edges)
        // canvas.sendBackwards(this.group)
    }
}
function randCoords(){
    return {x:(canvas.width)/3+(canvas.width/2)*Math.random(), y:(canvas.height/3) + (canvas.height/2)*Math.random()}
}
function render(data){
    for(var i=0;i<data.V.length;i++){
        console.log(data.V[i])
        let v = data.V[i]
        if(v.coords.x==0 &&v.coords.y==0){
            v.coords = randCoords()
        }
        if(v.color==""){
            v.color="cyan"
        }
        v.color="cyan"
        console.log(v.coords)
        V[v.ptr] = (new VNode(v.coords.x, v.coords.y, v.label, v.color,canvas))
    }
    for(var i=0;i<data.V.length;i++){
        let v = data.V[i];
        for(var j = 0;j<v.outlist.length;j++){
            
            if(E[v.outlist[j].ptr]==undefined && E[v.outlist[j].conjugate]==undefined){
                if(v.outlist[j].color==""){
                    v.outlist[j].color = "red"
                }
                E[v.outlist[j].ptr] = new Edge(V[v.ptr],V[v.outlist[j].end],v.outlist[j].label,v.outlist[j].color ,canvas); 
            }
            else{
    
            }
    
        }
    }
}
render(data)
canvas.on('object:moving', function(ev){
    let group = ev.transform.target
    console.log(group.edges);
    console.log(group.left, group.top)
    // let p = ev.transform.target
    for(var i=0;i<group.edges.length;i++){
        console.log(group.edges[i].left, group.edges[i].top)
        group.edges[i].set({'x1':group.left+ radroot, 'y1':group.top+ radroot})
        // group.edges[i].stroke = 10
        canvas.renderAll()
    }
    for(var i=0;i<group.edges2.length;i++){
        console.log(group.edges2[i].left, group.edges2[i].top)
        group.edges2[i].set({'x2':group.left+ radroot, 'y2':group.top+ radroot})
        // group.edges[i].stroke = 10
        canvas.renderAll()
    }
    
})
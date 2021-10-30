const initCanvas = (id)=>{
    return new fabric.Canvas(id, {
        width:500,
        height:500,
        backgroundColor:'#eef'
    })
}

class VNode{
    constructor(x, y, label, color,canvas){
        let radius = canvas.renderMeta.radius
        let radroot = Math.SQRT1_2*radius;
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
        this.group.node = this
        //console.log(canvas.add)
        canvas.add(this.group)
    }
    updateNode(data){
        this.shape.fill = data.color
        this.shape.x = data.x;this.x = data.x;
        this.shape.y = this.shape.canvas.height - data.y; this.y = data.y;
        this.text.text = data.label
        this.shape.cav
        console.log(this.text.text)
        console.log(data)
        this.shape.canvas.renderAll()
    }
}
class Edge{
    constructor(n1, n2, label, color,canvas){
        let noderadius = canvas.renderMeta.radius
        let radroot = Math.SQRT1_2*noderadius;
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
        // //console.log(n1.group.edges)
        // canvas.sendBackwards(this.group)
    }
}
function randCoords(canvas){
    return {x:(canvas.width)/3+(canvas.width/2)*Math.random(), y:(canvas.height/3) + (canvas.height/2)*Math.random()}
}
function render(data,canvas){
    canvas.backgroundColor = "#eef";
    //console.log(renderMeta.canvas)
    let renderMeta = canvas.renderMeta
    for(var i=0;i<data.V.length;i++){
        //console.log(data.V[i])
        let v = data.V[i]
        if(v.coords.x==0 &&v.coords.y==0){
            v.coords = randCoords(canvas)
        }
        if(v.color==""){
            v.color="cyan"
        }
        //console.log(v.coords)
        // if(renderMeta.V[v.ptr]==undefined){
            renderMeta.V[v.ptr] = (new VNode(v.coords.x, v.coords.y, v.label, v.color,canvas))
        // }

    }
    for(var i=0;i<data.V.length;i++){
        let v = data.V[i];
        for(var j = 0;j<v.outlist.length;j++){
            
            if(renderMeta.E[v.outlist[j].ptr]==undefined && renderMeta.E[v.outlist[j].conjugate]==undefined){
                if(v.outlist[j].color==""){
                    v.outlist[j].color = "red"
                }
                renderMeta.E[v.outlist[j].ptr] = new Edge(renderMeta.V[v.ptr],renderMeta.V[v.outlist[j].end],v.outlist[j].label,v.outlist[j].color,canvas); 
            }
            else{
    
            }
    
        }
    }
}
const nodeDrag = (ev)=>{
        let group = ev.transform.target
        //console.log(group.edges);
        // //console.log()
        let canvas = ev.target.canvas
        let renderMeta = ev.target.canvas.renderMeta
        let radius = renderMeta.radius
        let radroot = radius*Math.SQRT1_2
        //console.log(group.left, group.top)
        // let p = ev.transform.target
        for(var i=0;i<group.edges.length;i++){
            group.edges[i].set({'x1':group.left+ radroot, 'y1':group.top+ radroot})
            group.node.x = group.left;
            group.node.y = canvas.height - group.top;
            // canvas.renderAll()
        }
        for(var i=0;i<group.edges2.length;i++){
            //console.log(group.edges2[i].left, group.edges2[i].top)
            group.edges2[i].set({'x2':group.left+ radroot, 'y2':group.top+ radroot})
            // group.edges[i].stroke = 10
            group.node.x = group.left;
            group.node.y = canvas.height - group.top;
            
        }
        ev.target.canvas.renderAll()
}
function filterForServer(renderMeta){
    let V = renderMeta.V
    let toReturn = {};
    toReturn.V = [];
    // console.log(Object.keys(V))
    for(let v of Object.keys(V)){
        // console.log(V[v])
        toReturn.V.push({x:V[v].x, y:V[v].y});
    }
    toReturn.ptrs = Object.keys(V);
    return toReturn;
}
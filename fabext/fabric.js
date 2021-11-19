const initCanvas = (id)=>{
    return new fabric.Canvas(id, {
        width:700,
        height:650,
        backgroundColor:'#eef'
    })

}

class VNode{
    constructor(x, y, label, color,weight,metadata,canvas){
        let radius = canvas.renderMeta.radius
        let radroot = Math.SQRT1_2*radius;
        this.x = x
        this.y = y
        this.radroot = radroot
        this.label = label
        this.weight = weight
        this.color = color
        this.metadata = metadata
        // console.log(metadata)
        this.shape = new fabric.Circle({
            left:x,
            top:(canvas.height - y),
            strokeWidth:1,
            radius:radius,
            fill:color,
            stroke:'#666',
        })
        this.text = new fabric.Text(label.substr(0, 3), {
            left:x +radroot/2,
            top:(canvas.height - y+radroot/2),
            fontSize:7.5,
        })
        this.group = new fabric.Group([this.shape, this.text])
        this.group.hasControls = false;
        this.group.edges=[]
        this.group.edges2=[]
        this.group.node = this
        //console.log(canvas.add)
        canvas.add(this.group)
    }
    textdata(){
        let data = "Label:"+this.label+"\nWeight:"+this.weight+"\n(x="+parseInt(this.x).toString()+",y="+parseInt(this.y).toString()+")\n" + "Meta:"+this.metadata;
        return data;
    }
    updateNode(data){
        this.shape.fill = data.color
        this.shape.x = data.x;this.x = data.x;
        this.shape.y = this.shape.canvas.height - data.y; this.y = data.y;
        this.text.text = data.label
        // console.log(this.text.text)
        // console.log(data)
        this.shape.canvas.renderAll()
    }
    showData(){
        this.datatext = new fabric.Text(this.textdata(),{
            left:this.x +2*this.radroot,
            top:(this.group.canvas.height - this.y)+2*this.radroot,
            width:150,
            height:100,
            fontSize:15,
            fontWeight:'bold',
            fill:'darkgreen',
        })
        this.datarect = new fabric.Rect({
            left:this.x+2*this.radroot,
            top:(this.group.canvas.height - this.y)+2*this.radroot,
            width:150,
            height:80,
            fill:'#fffdd0',
            hasBorders:true,
            strokeWidth:1,
            stroke:'#000000'
        })
        

        this.group.datashape = new fabric.Group([this.datarect, this.datatext],{
            evented:false,
            selectable:false
        });
        
        this.group.canvas.add(this.group.datashape)
        // console.log("Called!")
        this.group.canvas.renderAll()
        
    }
    hideData(){
        // if(this.group.datashape!=undefined){
        try{
            //try catch block because of asynchronicity of js events
            this.group.canvas.remove(this.group.datashape)
            this.group.canvas.renderAll()
        }    
        catch(e){

        }
        // }
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
        // console.log(n1);
        this.line = new fabric.Line([n1.group.left + radroot, n1.group.top + radroot, n2.group.left+radroot, n2.group.top + radroot],{
            fill:color,
            stroke:color,
            strokeWidth:1.5,
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
function newrandCoords(canvas, miny,len_V){
    let w,h;
    let padf = 0.05;
    w = canvas.width;h = canvas.height;
    let dh = (1-padf)*h/len_V;
    let x,y;
    x = (canvas.width*(1-padf))*Math.random();
    y = Math.min(miny + dh, h*(1-padf));
    return {x:x, y:y}
}
function randCoords(canvas){
    return {x:(canvas.width)/3+(canvas.width/2)*Math.random(), y:(canvas.height/3) + (canvas.height/2)*Math.random()}
}
function clearEdges(renderMeta, V, canvas){
    E = renderMeta.E;
    for(var i=0;i<V.length;i++){
        let v = V[i];
        for(var j=0;j<v.outlist.length;j++){
            if(E[v.outlist[j].ptr]!=undefined){
                canvas.remove(E[v.outlist[j].ptr].line)
                delete E[v.outlist[j].ptr]
            }
            else if(E[v.outlist[j].conjugate]!=undefined){
                canvas.remove(E[v.outlist[j].conjugate].line)
                delete E[v.outlist[j].conjugate]
            }
        }
    }

}
function render(data,canvas){
    canvas.backgroundColor = "#eef";
    let renderMeta = canvas.renderMeta
    for(var i=0;i<data.V.length;i++){
        let v = data.V[i]
        if(v.coords.x==0 &&v.coords.y==0){
            v.coords = newrandCoords(canvas, data.V[Math.max(i-1,0)].coords.y, data.V.length);
        }
        if(v.color==""){
            v.color="cyan"
        }
        //console.log(v.coords)
        if(renderMeta.V[v.ptr]==undefined){
            renderMeta.V[v.ptr] = (new VNode(v.coords.x, v.coords.y, v.label, v.color,v.weight,v.meta,canvas))
        }
        else{
            canvas.remove(renderMeta.V[v.ptr].group);
            renderMeta.V[v.ptr].hideData();
            renderMeta.V[v.ptr] = (new VNode(v.coords.x, v.coords.y, v.label, v.color,v.weight,v.meta,canvas))
        }

    }
    clearEdges(renderMeta, data.V, canvas);
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
        group.node.hideData()
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
const displayData = (ev)=>{
    // console.log(ev)
    let group = ev.target
    if(!ev.target){
        return;
    }
    if(group.edges){
        group.node.showData()
    }

}
const hideData = (ev)=>{
    
    let group = ev.target
    if(!ev.target){
        return;
    }
    if(group.edges){
        group.node.hideData()        
    }

}
function filterForServer(canvas){
    let renderMeta_lastsynced = canvas.renderMeta_lastsynced
    let renderMeta = canvas.renderMeta
    let V = renderMeta.V
    let V_ls = renderMeta_lastsynced.V
    let toReturn = {};
    toReturn.V = [];
    let keysToReturn = []
    // console.log(Object.keys(V))
    for(let v of Object.keys(V)){
        if(V[v]!=V_ls[v]){
            // console.log(V[v])
            toReturn.V.push({x:V[v].x, y:V[v].y});
            keysToReturn.push(v);
        }
    }
    toReturn.ptrs = keysToReturn;
    return toReturn;
}
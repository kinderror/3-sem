[x,y,z,v] = flow;
p = patch(isosurface(x,y,z,v,-3)); 
isonormals(x,y,z,v,p)
p.FaceColor = 'red'; 
p.EdgeColor = 'none';
daspect([1 1 1])
view(3); 
axis tight
camlight 
lighting gouraud
hold on;
p = patch(isosurface(x,y,z,v,-5)); 
isonormals(x,y,z,v,p)
p.FaceColor = 'blue'; 
p.EdgeColor = 'none';
 p = patch(isosurface(x,y,z,v,-1)); 
isonormals(x,y,z,v,p)
p.FaceColor = [0 0.5 0];
p.EdgeColor = 'none';
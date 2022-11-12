

def main():
    file_path = "suzanne.obj"

    with open(file_path,'r') as file:
        file_lines = file.readlines()

    
    vertice = []
    edges = []
    

    for line in file_lines:
        if line[0] == 'v':
            [x,y,z] = line.strip().split()[1:]
            x = float(x)
            y = float(y)
            z = float(z)

            vertice.append((x,y,z))
        
        if line[0] == 'f':
            values = line.strip().split()[1:]
            
            for i in range(len(values)):
                edges.append((int(values[i]),int(values[(i+1)%len(values)])))

    with open("suzanne.pff",'w') as output_file:
        output_file.write(f"{len(vertice)}")
        output_file.write("\n")
        output_file.write(f"{len(edges)}")
        output_file.write("\n")
        output_file.write("\n")
        for (x,y,z) in vertice:
            output_file.write(f"{x} {y} {z}")
            output_file.write("\n")
        output_file.write("\n")
        for (i1,i2) in edges:
            output_file.write(f"{i1-1} {i2-1}")
            output_file.write("\n")

    



if __name__ == '__main__':
    main()

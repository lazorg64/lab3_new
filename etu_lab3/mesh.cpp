#include "mesh.h"

mesh::mesh(float inx,float iny,float inz)
{
    x=inx;
    y=iny;
    z=inz;
    scale=100;
}

GLvoid mesh::LoadGLTextures()
{
        pixmap1.load(QString("C:\\Users\\lazorg\\Documents\\GitHub\\game\\game\\Iphone5_diffuse.png"));
        if(pixmap1.isNull())
        {
            cerr << "pixmap file open error!"<<endl;
            exit(1);
        }
        pixmap2.load(QString("C:\\Users\\lazorg\\Documents\\GitHub\\game\\game\\Iphone5_Screen.png"));
        if(pixmap2.isNull())
        {
            cerr << "pixmap file open error!"<<endl;
            exit(1);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void mesh::loadModel(const char * path)
{
    ifstream file;
    file.open(path);

    if(!file.is_open())
    {
        cerr <<"file open error!"<<endl;
        exit(1);
    }

    string str;
    string current_mat="null";
    while(!file.eof())
    {
        file >> str;
        if(str=="v")
        {
            glm::vec3 vertex;
            file >> vertex.x;
            file >> vertex.y;
            file >> vertex.z;
            model.push_back(vertex);
        }
        else if(str=="vn")
        {
            glm::vec3 normal;
            file >> normal.x;
            file >> normal.y;
            file >> normal.z;
            normals.push_back(normal);
        }
        else if(str=="vt")
        {
            glm::vec2 tex;
            file >> tex.x;
            file >> tex.y;
            uvs.push_back(tex);
        }
        else if(str=="f")
        {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int ind=0;
            for(int i=0;i<3;i++)
            {
                file >> str;
                std::istringstream iss(str);
                std::string token;
                while(getline(iss, token, '/'))
                {
                    std::istringstream temp(token);
                    int in;
                    temp >> in;
                    if(ind==0)
                    vertexIndex[i]=in;
                    else if(ind==1)
                    uvIndex[i]=in;
                    else if(ind==2)
                    {
                    normalIndex[i]=in;
                    ind=-1;
                    }
                    ind++;
                }
            }
            materials.push_back(current_mat);
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else if(str=="usemtl")
        {
           file >> str;
           current_mat = str;
        }
    }
}



void mesh::draw(QGLWidget * parent)
{
    unsigned int a[4],b[4],c[4];
    int p=0,g=0;
    std::vector< unsigned int >::iterator it=vertexIndices.begin();
    std::vector< unsigned int >::iterator it2=uvIndices.begin();
    std::vector< unsigned int >::iterator it3=normalIndices.begin();
    std::vector< string >::iterator it4=materials.begin();
    while(it!=vertexIndices.end())
    {
        a[p]=*it;
        b[p]=*it2;
        c[p]=*it3;

        if(p==2)
        {
           if((it4.operator *())=="orig_01___Default")
               glBindTexture(GL_TEXTURE_2D, textureID[0]);
           else
               glBindTexture(GL_TEXTURE_2D, textureID[1]);

           p=0;
           glBegin(GL_TRIANGLES);
           glColor4d(1,1,1,1);

           glTexCoord2d(uvs[b[0]-1][0],uvs[b[0]-1][1]);
           glNormal3d((normals[c[0]-1][0]),(normals[c[0]-1][1]),(normals[c[0]-1][2]));
           glVertex3d((model[a[0]-1][0])/scale+x,(model[a[0]-1][1])/scale+y,(model[a[0]-1][2])/scale+z);

           glTexCoord2d(uvs[b[1]-1][0],uvs[b[1]-1][1]);
           glNormal3d((normals[c[1]-1][0]),(normals[c[1]-1][1]),(normals[c[1]-1][2]));
           glVertex3d((model[a[1]-1][0])/scale+x,(model[a[1]-1][1])/scale+y,(model[a[1]-1][2])/scale+z);

           glTexCoord2d(uvs[b[2]-1][0],uvs[b[2]-1][1]);
           glNormal3d((normals[c[2]-1][0]),(normals[c[2]-1][1]),(normals[c[2]-1][2]));
           glVertex3d((model[a[2]-1][0])/scale+x,(model[a[2]-1][1])/scale+y,(model[a[2]-1][2])/scale+z);
           glEnd();
           g++;
           it4++;
        }
        else
        {
            p++;
        }

        it++;
        it2++;
        it3++;

    }

}

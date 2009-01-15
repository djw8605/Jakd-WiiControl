#ifndef CMODEL3DS_H_
#define CMODEL3DS_H_

class CModel3DS
{
        public:
                CModel3DS(std::string filename);
                virtual void Draw() const;
                virtual void CreateVBO();
                virtual ~CModel3DS();
        protected:
                void GetFaces();
                unsigned int m_TotalFaces;
                Lib3dsFile * m_model;
                GLuint m_VertexVBO, m_NormalVBO;
};

#endif /*CMODEL3DS_H_*/

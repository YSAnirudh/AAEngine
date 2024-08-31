#pragma once
#include "RendererCommons.h"

namespace AAEngine {

	/*
	* Enum that defines all the Variable types that can be passed into AAEngine's Shaders.
	*/
	enum class EShaderVarType : uint8_t
	{
		None = 0,
		SVT_Float,
		SVT_Float2,
		SVT_Float3,
		SVT_Float4,
		SVT_Mat3,
		SVT_Mat4,
		SVT_Int,
		SVT_Int2,
		SVT_Int3,
		SVT_Int4,
		SVT_Bool,
	};

	/*
	* Function to convert AAEngine Shader Variable types to Size (sizeof(type) * Count) of the primitive types linked to those enums
	*/
	static constexpr uint32_t ShaderVariableTypeSize(EShaderVarType Type)
	{
		switch (Type)
		{
		case EShaderVarType::SVT_Float:		return sizeof(float) * 1;
		case EShaderVarType::SVT_Float2:	return sizeof(float) * 2;
		case EShaderVarType::SVT_Float3:	return sizeof(float) * 3;
		case EShaderVarType::SVT_Float4:	return sizeof(float) * 4;
		case EShaderVarType::SVT_Mat3:		return sizeof(float) * 3 * 3;
		case EShaderVarType::SVT_Mat4:		return sizeof(float) * 4 * 4;
		case EShaderVarType::SVT_Int:		return sizeof(int) * 1;
		case EShaderVarType::SVT_Int2:		return sizeof(int) * 2;
		case EShaderVarType::SVT_Int3:		return sizeof(int) * 3;
		case EShaderVarType::SVT_Int4:		return sizeof(int) * 4;
		case EShaderVarType::SVT_Bool:		return sizeof(bool) * 1;
		}
		return 0;
	}

	/*
	* Function to convert AAEngine Shader Variable types to Count of the primitive types linked to those enums
	*/
	static constexpr uint32_t ShaderVariableTypeCount(EShaderVarType Type) noexcept
	{
		switch (Type)
		{
		case EShaderVarType::SVT_Float:		return 1;
		case EShaderVarType::SVT_Float2:	return 2;
		case EShaderVarType::SVT_Float3:	return 3;
		case EShaderVarType::SVT_Float4:	return 4;
		case EShaderVarType::SVT_Mat3:		return 3 * 3;
		case EShaderVarType::SVT_Mat4:		return 4 * 4;
		case EShaderVarType::SVT_Int:		return 1;
		case EShaderVarType::SVT_Int2:		return 2;
		case EShaderVarType::SVT_Int3:		return 3;
		case EShaderVarType::SVT_Int4:		return 4;
		case EShaderVarType::SVT_Bool:		return 1;
		}
		return 0;
	}

	/*
	* Platform and API independent Vertex Buffer Element class.
	* 
	* Single element in an array Contains information required to define the Vertex Buffer Layout of the Shader
	*/
	struct FVertexBufferElement
	{
		/* 
		* Size of the Buffer Elements 
		* - sizeof * Count
		*/
		uint32_t Size;
		/* 
		* Offset of the Buffer Elements 
		* - sizeof * Position of the Element
		* - Ex: 0,0,0,0,0,0 = Position and Normal
		*		Position Offset = 0 * sizeof float
		*		Normal offset = 3 * sizeof float
		*		
		*/
		uint32_t Offset;
		/*
		* Name of the variable in the Shader
		*/
		std::string Name;
		/*
		* Vertex Input Type of the variable in the Shader
		*/
		EVertexInputType VertexInputType;
		/*
		* Data Type of the Shader Variable
		*/
		EShaderVarType Type;
		/*
		* Whether values should be normalized from 0.0f to 1.0f
		*/
		bool bShouldNormalize;

		/*
		* Default Constructor
		*/
		FVertexBufferElement() = default;

		/*
		* Constructor that takes in Variable type, the name of the variable in the Shader, and default parameter for whether values should be normalized
		* 
		* @param InVarType - Data Type of the Shader Variable
		* @param InVertexInputType - Vertex Input Type of the Shader Variable in the Shader
		* @param bShouldNormalize - Default Parameter for whether the values sent into the shader should be normalized between 0.0f and 1.0f
		*/
		FVertexBufferElement(EShaderVarType InVarType, EVertexInputType InVertexInputType, bool bShouldNormalize = false)
			: VertexInputType(InVertexInputType), Name(CRendererUtils::GetVertexInputName(InVertexInputType)), Type(InVarType), Size(ShaderVariableTypeSize(InVarType)), Offset(0), bShouldNormalize(bShouldNormalize)
		{
		}

		/*
		* Const Getter for the no of Components of a primitive data type the EShaderVarType represents
		*/
		FORCEINLINE constexpr uint32_t GetComponentCount() const noexcept { return ShaderVariableTypeCount(Type); }
	};

	/*
	* Platform and API independent Vertex Buffer Layout class.
	* 
	* Specifies the Layout of the variables passed into the Shader.
	* Ex:	OpenGL				--- layout(location = 0) in vec3 Position.
	*							--- layout(location = 1) in vec4 Color.
	*		VertexBufferLayout	--- {	
	*									{ EShaderVarType::Float3, "Position" },
	*									{ EShaderVarType::Float4, "Color" }
	*								};
	*/
	class CVertexBufferLayout
	{
	public:
		/*
		* Default Constructor
		*/
		CVertexBufferLayout() = default;

		/*
		* Constructor that takes in an Array
		*
		* @param const TArray<FVertexBufferElement>& - Array of Elements to be initialied in the Layout
		*/
		CVertexBufferLayout(const TArray<FVertexBufferElement>& Elements)
			: VertexBufferElements(Elements)
		{
			SetElementOffsetAndStride();
		}

		/*
		* Constructor that takes in an std::initializer_list
		* Used to easily set and Initialize our Layout.
		* 
		* @param const std::initializer_list<FVertexBufferElement>& - InitList of Elements to be initialied in the Layout
		*/
		CVertexBufferLayout(const std::initializer_list<FVertexBufferElement>& Elements)
			: VertexBufferElements(Elements)
		{
			SetElementOffsetAndStride();
		}

		/*
		* const Getter for the Elements in the Layout.
		* 
		* @returns TArray<FVertexBufferElement> - Array of Vertex Buffer Elements.
		*/
		FORCEINLINE TArray<FVertexBufferElement> GetElements() const { return VertexBufferElements; }
		/*
		* const Getter of the Stride for the Elements in the Layout.
		*
		* @returns uint32_t - Stride for the Elements in the Layout.
		*/
		FORCEINLINE uint32_t GetStride() const { return Stride; }

		/*
		* Iterators for easy looping for the Elements in the Layout
		*/
		TArray<FVertexBufferElement>::Iterator		begin()			{ return VertexBufferElements.begin(); }
		TArray<FVertexBufferElement>::Iterator		end()			{ return VertexBufferElements.end(); }
		TArray<FVertexBufferElement>::ConstIterator	begin() const	{ return VertexBufferElements.begin(); }
		TArray<FVertexBufferElement>::ConstIterator	end() const		{ return VertexBufferElements.end(); }

		static CVertexBufferLayout PhongLayout;

	private:
		/*
		* Private function to calculate Offsets for each element and the Stride for the Layout
		*/
		void SetElementOffsetAndStride()
		{
			uint32_t CurOffset = 0;
			for (FVertexBufferElement& Elem : VertexBufferElements)
			{
				Elem.Offset = CurOffset;
				CurOffset += Elem.Size;
				Stride += Elem.Size;
			}
		}

	private:
		/*
		* Array of Vertex Buffer Elements.
		*/
		TArray<FVertexBufferElement> VertexBufferElements;
		/*
		* Stride of All the elements combined.
		* 
		* [] = {1,2,3,4,5,6} = 2 vec3s
		* Stride = 3
		*/
		uint32_t Stride{ 0 };
	};

	/*
	* Platform and API independent Vertex Buffer Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IVertexBuffer
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IVertexBuffer() {}

		/*
		* Pure virtual Bind function to Bind to the Vertex Buffer.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind from the Vertex Buffer.
		*/
		virtual void UnBind() = 0;

		/*
		* Pure virtual getter GetVertexCount function to get the number of Vertices.
		*
		* @returns Number for Vertices
		*/
		virtual uint32_t GetVertexCount() const = 0;

		/*
		* Const Getter for the Layout of the Vertex Buffer
		* 
		* @returns Layout of the Vertex Buffer (CVertexBufferLayout)
		*/
		CVertexBufferLayout GetLayout() const { return VertexBufferLayout; }
		/*
		* Setter for the Layout of the Vertex Buffer
		*
		* @param const CVertexBufferLayout& - Layout of the Vertex Buffer
		*/
		void SetLayout(const CVertexBufferLayout& Layout) { VertexBufferLayout = Layout; }

		/*
		* Static create method as create method doesn't vary based on instances.
		* 
		* @param Vertices - float pointer of Vertices. Array passed in as a pointer.
		* @param Count - size_t Count of the vertices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		* 
		* @returns A Platform indepentent Vertex Buffer
		*/
		static TSharedPtr<IVertexBuffer> Create(float* Vertices, uint32_t Count, uint32_t EnumUsage);
	private:
		/*
		* Layout of the Vertex Buffer
		*/
		CVertexBufferLayout VertexBufferLayout;
	};

	/*
	* Platform and API independent Index Buffer Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IIndexBuffer
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IIndexBuffer() {}

		/*
		* Pure virtual Bind function to Bind to the Index Buffer.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind from the Index Buffer.
		*/
		virtual void UnBind() = 0;

		/*
		* Pure virtual getter GetIndexCount function to get the number of Indices.
		*
		* @returns Number for Indices
		*/
		virtual uint32_t GetIndexCount() const = 0;

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param Indices - float pointer of Indices. Array passed in as a pointer.
		* @param Count - size_t Count of the Indices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		* 
		* @returns A Platform indepentent Index Buffer
		*/
		static TSharedPtr<IIndexBuffer> Create(uint32_t* Indices, uint32_t Count, uint32_t EnumUsage);
	};

	enum class EAttachmentType
	{
		AT_None = 0,
		AT_Color,
		AT_Depth,
		AT_DepthStencil,
	};

	enum class EFramebufferMode
	{
		FM_None = 0,
		FM_Write,
		FM_Read
	};

	class ITexture2D;
	class IFramebuffer
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IFramebuffer() {}

		/*
		* Pure virtual Bind function to Bind to the Framebuffer.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind from the Framebuffer.
		*/
		virtual void UnBind() = 0;

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param Indices - float pointer of Indices. Array passed in as a pointer.
		* @param Count - size_t Count of the Indices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		*
		* @returns A Platform indepentent Index Buffer
		*/
		static TSharedPtr<IFramebuffer> Create(ITexture2D* Texture, EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex = 0, EFramebufferMode FramebufferMode = EFramebufferMode::FM_None);
	};
}
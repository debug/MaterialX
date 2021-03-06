//
// TM & (c) 2017 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#ifndef MATERIALX_DEFINITION_H
#define MATERIALX_DEFINITION_H

/// @file
/// Definition element subclasses

#include <MaterialXCore/Library.h>

#include <MaterialXCore/Interface.h>

namespace MaterialX
{

extern const string COLOR_SEMANTIC;
extern const string SHADER_SEMANTIC;

/// A shared pointer to a NodeDef
using NodeDefPtr = shared_ptr<class NodeDef>;
/// A shared pointer to a const NodeDef
using ConstNodeDefPtr = shared_ptr<const class NodeDef>;

/// A shared pointer to an Implementation
using ImplementationPtr = shared_ptr<class Implementation>;
/// A shared pointer to a const Implementation
using ConstImplementationPtr = shared_ptr<const class Implementation>;

/// A shared pointer to a TypeDef
using TypeDefPtr = shared_ptr<class TypeDef>;
/// A shared pointer to a Member
using MemberPtr = shared_ptr<class Member>;

/// @class NodeDef
/// A node definition element within a Document.
///
/// A NodeDef provides the declaration of a node interface, which may then
/// be instantiated as a Node or a ShaderRef.
class NodeDef : public InterfaceElement
{
  public:
    NodeDef(ElementPtr parent, const string& name) :
        InterfaceElement(parent, CATEGORY, name)
    {
    }
    virtual ~NodeDef() { }

    using ShaderRefPtr = shared_ptr<class ShaderRef>;

    /// @name Node String
    /// @{

    /// Set the node string of the NodeDef.
    void setNodeString(const string& node)
    {
        setAttribute(NODE_ATTRIBUTE, node);
    }

    /// Return true if the given NodeDef has a node string.
    bool hasNodeString() const
    {
        return hasAttribute(NODE_ATTRIBUTE);
    }

    /// Return the node string of the NodeDef.
    const string& getNodeString() const
    {
        return getAttribute(NODE_ATTRIBUTE);
    }

    /// @}
    /// @name Implementation References
    /// @{

    /// Return the first implementation for this nodedef, optionally filtered
    /// by the given target name.
    /// @param target An optional target name, which will be used to filter
    ///    the implementations that are considered.
    /// @return An implementation for this nodedef, or an empty shared pointer
    ///    if none was found.  Note that a node implementation may be either
    ///    an Implementation element or a NodeGraph element.
    InterfaceElementPtr getImplementation(const string& target = EMPTY_STRING) const;

    /// @}
    /// @name Shader References
    /// @{

    /// Return all ShaderRef elements that instantiate this NodeDef.
    vector<ShaderRefPtr> getInstantiatingShaderRefs() const;

    /// @}
    /// @name Validation
    /// @{

    /// Validate that the given element tree, including all descendants, is
    /// consistent with the MaterialX specification.
    bool validate(string* message = nullptr) const override;

    /// @}

  public:
    static const string CATEGORY;
    static const string NODE_ATTRIBUTE;
};

/// @class Implementation
/// An implementation element within a Document.
///
/// An Implementation is used to associate external source code with a specific
/// NodeDef, providing a definition for the node that may eiher be universal or
/// restricted to a specific target.
class Implementation : public InterfaceElement
{
  public:
    Implementation(ElementPtr parent, const string& name) :
        InterfaceElement(parent, CATEGORY, name)
    {
    }
    virtual ~Implementation() { }

    /// @name NodeDef
    /// @{

    /// Set the NodeDef string for the Implementation.
    void setNodeDefString(const string& nodeDef)
    {
        setAttribute(NODE_DEF_ATTRIBUTE, nodeDef);
    }

    /// Return true if the given Implementation has a NodeDef string.
    bool hasNodeDefString() const
    {
        return hasAttribute(NODE_DEF_ATTRIBUTE);
    }

    /// Return the NodeDef string for the Implementation.
    const string& getNodeDefString() const
    {
        return getAttribute(NODE_DEF_ATTRIBUTE);
    }

    /// Set the NodeDef element for the Implementation.
    void setNodeDef(NodeDefPtr nodeDef)
    {
        if (nodeDef)
        {
            setNodeDefString(nodeDef->getName());
        }
        else
        {
            removeAttribute(NODE_DEF_ATTRIBUTE);
        }
    }

    /// Return the NodeDef element for the Implementation.
    NodeDefPtr getNodeDef() const;

    /// @}
    /// @name File String
    /// @{

    /// Set the file string for the Implementation.
    void setFile(const string& file)
    {
        setAttribute(FILE_ATTRIBUTE, file);
    }

    /// Return true if the given Implementation has a file string.
    bool hasFile() const
    {
        return hasAttribute(FILE_ATTRIBUTE);
    }

    /// Return the file string for the Implementation.
    const string& getFile() const
    {
        return getAttribute(FILE_ATTRIBUTE);
    }

    /// @}
    /// @name Function String
    /// @{

    /// Set the function string for the Implementation.
    void setFunction(const string& function)
    {
        setAttribute(FUNCTION_ATTRIBUTE, function);
    }

    /// Return true if the given Implementation has a function string.
    bool hasFunction() const
    {
        return hasAttribute(FUNCTION_ATTRIBUTE);
    }

    /// Return the function string for the Implementation.
    const string& getFunction() const
    {
        return getAttribute(FUNCTION_ATTRIBUTE);
    }

    /// @}
    /// @name Language String
    /// @{

    /// Set the language string for the Implementation.
    void setLanguage(const string& language)
    {
        setAttribute(LANGUAGE_ATTRIBUTE, language);
    }

    /// Return true if the given Implementation has a language string.
    bool hasLanguage() const
    {
        return hasAttribute(LANGUAGE_ATTRIBUTE);
    }

    /// Return the language string for the Implementation.
    const string& getLanguage() const
    {
        return getAttribute(LANGUAGE_ATTRIBUTE);
    }

    /// @}

public:
    static const string CATEGORY;
    static const string NODE_DEF_ATTRIBUTE;
    static const string FILE_ATTRIBUTE;
    static const string FUNCTION_ATTRIBUTE;
    static const string LANGUAGE_ATTRIBUTE;
};

/// @class TypeDef
/// A type definition element within a Document.
class TypeDef : public Element
{
  public:
    TypeDef(ElementPtr parent, const string& name) :
        Element(parent, CATEGORY, name)
    {
    }
    virtual ~TypeDef() { }

    /// @name Semantic
    /// @{

    /// Set the semantic string of the TypeDef.
    void setSemantic(const string& semantic)
    {
        setAttribute(SEMANTIC_ATTRIBUTE, semantic);
    }

    /// Return true if the given TypeDef has a semantic string.
    bool hasSemantic() const
    {
        return hasAttribute(SEMANTIC_ATTRIBUTE);
    }

    /// Return the semantic string of the TypeDef.
    const string& getSemantic() const
    {
        return getAttribute(SEMANTIC_ATTRIBUTE);
    }

    /// @}
    /// @name Context
    /// @{

    /// Set the context string of the TypeDef.
    void setContext(const string& context)
    {
        setAttribute(CONTEXT_ATTRIBUTE, context);
    }

    /// Return true if the given TypeDef has a context string.
    bool hasContext() const
    {
        return hasAttribute(CONTEXT_ATTRIBUTE);
    }

    /// Return the context string of the TypeDef.
    const string& getContext() const
    {
        return getAttribute(CONTEXT_ATTRIBUTE);
    }

    /// @}
    /// @name Member Elements
    /// @{

    /// Add a Member to the TypeDef.
    /// @param name The name of the new Member.
    ///     If no name is specified, then a unique name will automatically be
    ///     generated.
    /// @return A shared pointer to the new Member.
    MemberPtr addMember(const string& name = EMPTY_STRING)
    {
        return addChild<Member>(name);
    }

    /// Return the Member, if any, with the given name.
    MemberPtr getMember(const string& name) const
    {
        return getChildOfType<Member>(name);
    }

    /// Return a vector of all Member elements in the TypeDef.
    vector<MemberPtr> getMembers() const
    {
        return getChildrenOfType<Member>();
    }

    /// Remove the Member, if any, with the given name.
    void removeMember(const string& name)
    {
        removeChildOfType<Member>(name);
    }

    /// @}

  public:
    static const string CATEGORY;
    static const string SEMANTIC_ATTRIBUTE;
    static const string CONTEXT_ATTRIBUTE;
};

/// @class Member
/// A member element within a TypeDef.
class Member : public TypedElement
{
  public:
    Member(ElementPtr parent, const string& name) :
        TypedElement(parent, CATEGORY, name)
    {
    }
    virtual ~Member() { }

  public:
    static const string CATEGORY;
};

} // namespace MaterialX

#endif

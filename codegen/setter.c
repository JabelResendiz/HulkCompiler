

#include "codegen.h"

LLVMValueRef codegen_attr_setter(LLVMVisitor *v, ASTNode *node)
{

    ASTNode *instance_node = node->data.cond_node.cond;

    LLVMValueRef object_instance_ptr = codegen_accept(v, instance_node);

    if (!object_instance_ptr)
    {
        return NULL;
    }

    // 2. Obtener la infomacion de tipo para objectos
    const char *object_type_name = instance_node->return_type->name;
    LLVMUserTypeInfo *type_info = find_user_type(v->ctx, object_type_name);

    if (!type_info)
    {
        return NULL;
    }

    // 3. Obtener el nombre del atributo y encontrar su indice dentro de la estructura
    // el nombre del atributo est en data.cond_node.body_true (el node del miembro)
    ASTNode *member_node = node->data.cond_node.body_true;

    if (member_node->type != NODE_VARIABLE)
    { // Asume que el miembro es un acceso a variable o un ID
        return NULL;
    }
    const char *attribute_name = member_node->data.variable_name; // Asumiendo que el nombre de la variable es el nombre del atributo

    int attribute_index = find_field_index(type_info, attribute_name);

    if (attribute_index == -1)
    {
        return NULL;
    }

    // 4. Obtener la información completa del miembro (incluyendo su tipo LLVM)
    LLVMTypeMemberInfo *member_info = find_member_info(type_info, attribute_name);
    if (!member_info || !member_info->llvm_type)
    {
        return NULL;
    }
    LLVMTypeRef attribute_llvm_type = member_info->llvm_type;

    // 5. Generar la instrucción Get Element Pointer (GEP)
    // Esto nos da un PUNTERO a la ubicación de memoria del atributo.
    LLVMValueRef attribute_ptr = LLVMBuildStructGEP2(
        v->ctx->builder,
        type_info->struct_type, // El tipo de la estructura (ej. %A)
        object_instance_ptr,    // Puntero a la instancia del objeto (ej. %self_ptr)
        attribute_index,        // El índice del miembro
        attribute_name          // Nombre para la instrucción
    );

    // 6. Generar código para el valor que se va a asignar (el lado derecho de la asignación)
    // El valor a asignar está en data.cond_node.body_false
    ASTNode *value_node = node->data.cond_node.body_false;
    LLVMValueRef value_to_store = codegen_accept(v, value_node);

    if (!value_to_store)
    {
        return NULL;
    }


    // 7. Generar la instrucción Store (almacenar)
    // Esto guarda el 'value_to_store' en la dirección de memoria apuntada por 'attribute_ptr'.
    LLVMValueRef store_inst = LLVMBuildStore(
        v->ctx->builder,
        value_to_store, // El valor que se va a almacenar
        attribute_ptr   // La dirección donde se va a almacenar
    );

    // Los setters generalmente no "retornan" un valor en LLVM IR puro,
    // pero si tu lenguaje permite encadenar asignaciones (como 'a = b = 5'),
    // podrías retornar 'value_to_store'. Si no, NULL es una opción válida.
    return value_to_store;
}
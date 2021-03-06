
#ifdef HAVE_CONFIG_H
#include "../../../../../ext_config.h"
#endif

#include <php.h>
#include "../../../../../php_ext.h"
#include "../../../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/exception.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/concat.h"
#include "kernel/operators.h"
#include "kernel/array.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_Model_MetaData_Strategy_Annotations) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Mvc\\Model\\MetaData\\Strategy, Annotations, phalcon, mvc_model_metadata_strategy_annotations, phalcon_mvc_model_metadata_strategy_annotations_method_entry, 0);

	zend_class_implements(phalcon_mvc_model_metadata_strategy_annotations_ce TSRMLS_CC, 1, phalcon_mvc_model_metadata_strategyinterface_ce);
	return SUCCESS;

}

/**
 * Read the model's column map, this can't be inferred
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData_Strategy_Annotations, getColumnMaps) {

	zend_string *_7;
	zend_ulong _6;
	zend_bool hasReversedColumn = 0, _10$$6;
	zval orderedColumnMap, reversedColumnMap;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, *container, container_sub, __$null, annotations, className, reflection, propertiesAnnotations, property, propAnnotations, columnAnnotation, columnName, _0, *_5, _1$$4, _2$$4, _3$$5, _4$$5, _8$$6, _9$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&annotations);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&propertiesAnnotations);
	ZVAL_UNDEF(&property);
	ZVAL_UNDEF(&propAnnotations);
	ZVAL_UNDEF(&columnAnnotation);
	ZVAL_UNDEF(&columnName);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&orderedColumnMap);
	ZVAL_UNDEF(&reversedColumnMap);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &model, &container);



	if (UNEXPECTED(Z_TYPE_P(container) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector is invalid", "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 33);
		return;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "annotations");
	ZEPHIR_CALL_METHOD(&annotations, container, "get", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, model, 0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&reflection, &annotations, "get", NULL, 0, &className);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&reflection) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZEPHIR_CONCAT_SV(&_2$$4, "No annotations were found in class ", &className);
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 1, &_2$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 44 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&propertiesAnnotations, &reflection, "getpropertiesannotations", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!(zephir_fast_count_int(&propertiesAnnotations TSRMLS_CC)))) {
		ZEPHIR_INIT_VAR(&_3$$5);
		object_init_ex(&_3$$5, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_4$$5);
		ZEPHIR_CONCAT_SV(&_4$$5, "No properties with annotations were found in class ", &className);
		ZEPHIR_CALL_METHOD(NULL, &_3$$5, "__construct", NULL, 1, &_4$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$5, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 55 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&orderedColumnMap);
	array_init(&orderedColumnMap);
	ZEPHIR_INIT_VAR(&reversedColumnMap);
	array_init(&reversedColumnMap);
	hasReversedColumn = 0;
	zephir_is_iterable(&propertiesAnnotations, 0, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 92);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&propertiesAnnotations), _6, _7, _5)
	{
		ZEPHIR_INIT_NVAR(&property);
		if (_7 != NULL) { 
			ZVAL_STR_COPY(&property, _7);
		} else {
			ZVAL_LONG(&property, _6);
		}
		ZEPHIR_INIT_NVAR(&propAnnotations);
		ZVAL_COPY(&propAnnotations, _5);
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Column");
		ZEPHIR_CALL_METHOD(&_8$$6, &propAnnotations, "has", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (!(zephir_is_true(&_8$$6))) {
			continue;
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Column");
		ZEPHIR_CALL_METHOD(&columnAnnotation, &propAnnotations, "get", NULL, 0, &_9$$6);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "column");
		ZEPHIR_CALL_METHOD(&columnName, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (ZEPHIR_IS_EMPTY(&columnName)) {
			ZEPHIR_CPY_WRT(&columnName, &property);
		}
		zephir_array_update_zval(&orderedColumnMap, &columnName, &property, PH_COPY | PH_SEPARATE);
		zephir_array_update_zval(&reversedColumnMap, &property, &columnName, PH_COPY | PH_SEPARATE);
		_10$$6 = !hasReversedColumn;
		if (_10$$6) {
			_10$$6 = !ZEPHIR_IS_EQUAL(&columnName, &property);
		}
		if (_10$$6) {
			hasReversedColumn = 1;
		}
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&propAnnotations);
	ZEPHIR_INIT_NVAR(&property);
	if (!(hasReversedColumn)) {
		zephir_create_array(return_value, 2, 0 TSRMLS_CC);
		zephir_array_fast_append(return_value, &__$null);
		zephir_array_fast_append(return_value, &__$null);
		RETURN_MM();
	}
	zephir_create_array(return_value, 2, 0 TSRMLS_CC);
	zephir_array_fast_append(return_value, &orderedColumnMap);
	zephir_array_fast_append(return_value, &reversedColumnMap);
	RETURN_MM();

}

/**
 * The meta-data is obtained by reading the column descriptions from the database information schema
 */
PHP_METHOD(Phalcon_Mvc_Model_MetaData_Strategy_Annotations, getMetaData) {

	zend_bool _70$$6;
	zend_string *_7;
	zend_ulong _6;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *model, model_sub, *container, container_sub, __$true, annotations, className, reflection, propertiesAnnotations, property, propAnnotations, columnAnnotation, columnName, feature, fieldTypes, fieldBindTypes, numericTyped, primaryKeys, nonPrimaryKeys, identityField, notNull, attributes, defaultValues, defaultValue, emptyStringValues, skipOnInsert, skipOnUpdate, _0, *_5, _1$$4, _2$$4, _3$$5, _4$$5, _8$$6, _9$$6, _64$$6, _65$$6, _66$$6, _67$$6, _68$$6, _69$$6, _71$$6, _10$$9, _11$$9, _12$$10, _13$$10, _14$$11, _15$$11, _16$$12, _17$$12, _18$$13, _19$$13, _20$$14, _21$$14, _22$$15, _23$$15, _24$$16, _25$$16, _26$$17, _27$$17, _28$$18, _29$$18, _30$$19, _31$$19, _32$$20, _33$$20, _34$$21, _35$$21, _36$$22, _37$$22, _38$$23, _39$$23, _40$$24, _41$$24, _42$$25, _43$$25, _44$$26, _45$$26, _46$$27, _47$$27, _48$$28, _49$$28, _50$$29, _51$$29, _52$$30, _53$$30, _54$$31, _55$$31, _56$$32, _57$$32, _58$$33, _59$$33, _60$$34, _61$$34, _62$$35, _63$$35;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&model_sub);
	ZVAL_UNDEF(&container_sub);
	ZVAL_BOOL(&__$true, 1);
	ZVAL_UNDEF(&annotations);
	ZVAL_UNDEF(&className);
	ZVAL_UNDEF(&reflection);
	ZVAL_UNDEF(&propertiesAnnotations);
	ZVAL_UNDEF(&property);
	ZVAL_UNDEF(&propAnnotations);
	ZVAL_UNDEF(&columnAnnotation);
	ZVAL_UNDEF(&columnName);
	ZVAL_UNDEF(&feature);
	ZVAL_UNDEF(&fieldTypes);
	ZVAL_UNDEF(&fieldBindTypes);
	ZVAL_UNDEF(&numericTyped);
	ZVAL_UNDEF(&primaryKeys);
	ZVAL_UNDEF(&nonPrimaryKeys);
	ZVAL_UNDEF(&identityField);
	ZVAL_UNDEF(&notNull);
	ZVAL_UNDEF(&attributes);
	ZVAL_UNDEF(&defaultValues);
	ZVAL_UNDEF(&defaultValue);
	ZVAL_UNDEF(&emptyStringValues);
	ZVAL_UNDEF(&skipOnInsert);
	ZVAL_UNDEF(&skipOnUpdate);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_64$$6);
	ZVAL_UNDEF(&_65$$6);
	ZVAL_UNDEF(&_66$$6);
	ZVAL_UNDEF(&_67$$6);
	ZVAL_UNDEF(&_68$$6);
	ZVAL_UNDEF(&_69$$6);
	ZVAL_UNDEF(&_71$$6);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$10);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_15$$11);
	ZVAL_UNDEF(&_16$$12);
	ZVAL_UNDEF(&_17$$12);
	ZVAL_UNDEF(&_18$$13);
	ZVAL_UNDEF(&_19$$13);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_22$$15);
	ZVAL_UNDEF(&_23$$15);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$16);
	ZVAL_UNDEF(&_26$$17);
	ZVAL_UNDEF(&_27$$17);
	ZVAL_UNDEF(&_28$$18);
	ZVAL_UNDEF(&_29$$18);
	ZVAL_UNDEF(&_30$$19);
	ZVAL_UNDEF(&_31$$19);
	ZVAL_UNDEF(&_32$$20);
	ZVAL_UNDEF(&_33$$20);
	ZVAL_UNDEF(&_34$$21);
	ZVAL_UNDEF(&_35$$21);
	ZVAL_UNDEF(&_36$$22);
	ZVAL_UNDEF(&_37$$22);
	ZVAL_UNDEF(&_38$$23);
	ZVAL_UNDEF(&_39$$23);
	ZVAL_UNDEF(&_40$$24);
	ZVAL_UNDEF(&_41$$24);
	ZVAL_UNDEF(&_42$$25);
	ZVAL_UNDEF(&_43$$25);
	ZVAL_UNDEF(&_44$$26);
	ZVAL_UNDEF(&_45$$26);
	ZVAL_UNDEF(&_46$$27);
	ZVAL_UNDEF(&_47$$27);
	ZVAL_UNDEF(&_48$$28);
	ZVAL_UNDEF(&_49$$28);
	ZVAL_UNDEF(&_50$$29);
	ZVAL_UNDEF(&_51$$29);
	ZVAL_UNDEF(&_52$$30);
	ZVAL_UNDEF(&_53$$30);
	ZVAL_UNDEF(&_54$$31);
	ZVAL_UNDEF(&_55$$31);
	ZVAL_UNDEF(&_56$$32);
	ZVAL_UNDEF(&_57$$32);
	ZVAL_UNDEF(&_58$$33);
	ZVAL_UNDEF(&_59$$33);
	ZVAL_UNDEF(&_60$$34);
	ZVAL_UNDEF(&_61$$34);
	ZVAL_UNDEF(&_62$$35);
	ZVAL_UNDEF(&_63$$35);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &model, &container);



	if (UNEXPECTED(Z_TYPE_P(container) != IS_OBJECT)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_model_exception_ce, "The dependency injector is invalid", "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 114);
		return;
	}
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "annotations");
	ZEPHIR_CALL_METHOD(&annotations, container, "get", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&className);
	zephir_get_class(&className, model, 0 TSRMLS_CC);
	ZEPHIR_CALL_METHOD(&reflection, &annotations, "get", NULL, 0, &className);
	zephir_check_call_status();
	if (UNEXPECTED(Z_TYPE_P(&reflection) != IS_OBJECT)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_2$$4);
		ZEPHIR_CONCAT_SV(&_2$$4, "No annotations were found in class ", &className);
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 1, &_2$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 125 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&propertiesAnnotations, &reflection, "getpropertiesannotations", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!(zephir_fast_count_int(&propertiesAnnotations TSRMLS_CC)))) {
		ZEPHIR_INIT_VAR(&_3$$5);
		object_init_ex(&_3$$5, phalcon_mvc_model_exception_ce);
		ZEPHIR_INIT_VAR(&_4$$5);
		ZEPHIR_CONCAT_SV(&_4$$5, "No properties with annotations were found in class ", &className);
		ZEPHIR_CALL_METHOD(NULL, &_3$$5, "__construct", NULL, 1, &_4$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$5, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 136 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&attributes);
	array_init(&attributes);
	ZEPHIR_INIT_VAR(&primaryKeys);
	array_init(&primaryKeys);
	ZEPHIR_INIT_VAR(&nonPrimaryKeys);
	array_init(&nonPrimaryKeys);
	ZEPHIR_INIT_VAR(&numericTyped);
	array_init(&numericTyped);
	ZEPHIR_INIT_VAR(&notNull);
	array_init(&notNull);
	ZEPHIR_INIT_VAR(&fieldTypes);
	array_init(&fieldTypes);
	ZEPHIR_INIT_VAR(&fieldBindTypes);
	array_init(&fieldBindTypes);
	ZEPHIR_INIT_VAR(&identityField);
	ZVAL_BOOL(&identityField, 0);
	ZEPHIR_INIT_VAR(&skipOnInsert);
	array_init(&skipOnInsert);
	ZEPHIR_INIT_VAR(&skipOnUpdate);
	array_init(&skipOnUpdate);
	ZEPHIR_INIT_VAR(&defaultValues);
	array_init(&defaultValues);
	ZEPHIR_INIT_VAR(&emptyStringValues);
	array_init(&emptyStringValues);
	zephir_is_iterable(&propertiesAnnotations, 0, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 393);
	ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&propertiesAnnotations), _6, _7, _5)
	{
		ZEPHIR_INIT_NVAR(&property);
		if (_7 != NULL) { 
			ZVAL_STR_COPY(&property, _7);
		} else {
			ZVAL_LONG(&property, _6);
		}
		ZEPHIR_INIT_NVAR(&propAnnotations);
		ZVAL_COPY(&propAnnotations, _5);
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Column");
		ZEPHIR_CALL_METHOD(&_8$$6, &propAnnotations, "has", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (!(zephir_is_true(&_8$$6))) {
			continue;
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Column");
		ZEPHIR_CALL_METHOD(&columnAnnotation, &propAnnotations, "get", NULL, 0, &_9$$6);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "column");
		ZEPHIR_CALL_METHOD(&columnName, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (ZEPHIR_IS_EMPTY(&columnName)) {
			ZEPHIR_CPY_WRT(&columnName, &property);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "type");
		ZEPHIR_CALL_METHOD(&feature, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		do {
			if (ZEPHIR_IS_STRING(&feature, "biginteger")) {
				ZEPHIR_INIT_NVAR(&_10$$9);
				ZVAL_LONG(&_10$$9, 14);
				zephir_array_update_zval(&fieldTypes, &columnName, &_10$$9, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_11$$9);
				ZVAL_LONG(&_11$$9, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_11$$9, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "bit")) {
				ZEPHIR_INIT_NVAR(&_12$$10);
				ZVAL_LONG(&_12$$10, 19);
				zephir_array_update_zval(&fieldTypes, &columnName, &_12$$10, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_13$$10);
				ZVAL_LONG(&_13$$10, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_13$$10, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "blob")) {
				ZEPHIR_INIT_NVAR(&_14$$11);
				ZVAL_LONG(&_14$$11, 11);
				zephir_array_update_zval(&fieldTypes, &columnName, &_14$$11, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_15$$11);
				ZVAL_LONG(&_15$$11, 3);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_15$$11, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "boolean")) {
				ZEPHIR_INIT_NVAR(&_16$$12);
				ZVAL_LONG(&_16$$12, 8);
				zephir_array_update_zval(&fieldTypes, &columnName, &_16$$12, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_17$$12);
				ZVAL_LONG(&_17$$12, 5);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_17$$12, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "char")) {
				ZEPHIR_INIT_NVAR(&_18$$13);
				ZVAL_LONG(&_18$$13, 5);
				zephir_array_update_zval(&fieldTypes, &columnName, &_18$$13, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_19$$13);
				ZVAL_LONG(&_19$$13, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_19$$13, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "date")) {
				ZEPHIR_INIT_NVAR(&_20$$14);
				ZVAL_LONG(&_20$$14, 1);
				zephir_array_update_zval(&fieldTypes, &columnName, &_20$$14, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_21$$14);
				ZVAL_LONG(&_21$$14, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_21$$14, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "datetime")) {
				ZEPHIR_INIT_NVAR(&_22$$15);
				ZVAL_LONG(&_22$$15, 4);
				zephir_array_update_zval(&fieldTypes, &columnName, &_22$$15, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_23$$15);
				ZVAL_LONG(&_23$$15, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_23$$15, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "decimal")) {
				ZEPHIR_INIT_NVAR(&_24$$16);
				ZVAL_LONG(&_24$$16, 3);
				zephir_array_update_zval(&fieldTypes, &columnName, &_24$$16, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_25$$16);
				ZVAL_LONG(&_25$$16, 32);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_25$$16, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "double")) {
				ZEPHIR_INIT_NVAR(&_26$$17);
				ZVAL_LONG(&_26$$17, 9);
				zephir_array_update_zval(&fieldTypes, &columnName, &_26$$17, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_27$$17);
				ZVAL_LONG(&_27$$17, 32);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_27$$17, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "enum")) {
				ZEPHIR_INIT_NVAR(&_28$$18);
				ZVAL_LONG(&_28$$18, 18);
				zephir_array_update_zval(&fieldTypes, &columnName, &_28$$18, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_29$$18);
				ZVAL_LONG(&_29$$18, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_29$$18, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "float")) {
				ZEPHIR_INIT_NVAR(&_30$$19);
				ZVAL_LONG(&_30$$19, 7);
				zephir_array_update_zval(&fieldTypes, &columnName, &_30$$19, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_31$$19);
				ZVAL_LONG(&_31$$19, 32);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_31$$19, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "integer")) {
				ZEPHIR_INIT_NVAR(&_32$$20);
				ZVAL_LONG(&_32$$20, 0);
				zephir_array_update_zval(&fieldTypes, &columnName, &_32$$20, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_33$$20);
				ZVAL_LONG(&_33$$20, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_33$$20, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "json")) {
				ZEPHIR_INIT_NVAR(&_34$$21);
				ZVAL_LONG(&_34$$21, 15);
				zephir_array_update_zval(&fieldTypes, &columnName, &_34$$21, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_35$$21);
				ZVAL_LONG(&_35$$21, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_35$$21, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "jsonb")) {
				ZEPHIR_INIT_NVAR(&_36$$22);
				ZVAL_LONG(&_36$$22, 16);
				zephir_array_update_zval(&fieldTypes, &columnName, &_36$$22, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_37$$22);
				ZVAL_LONG(&_37$$22, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_37$$22, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "longblob")) {
				ZEPHIR_INIT_NVAR(&_38$$23);
				ZVAL_LONG(&_38$$23, 13);
				zephir_array_update_zval(&fieldTypes, &columnName, &_38$$23, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_39$$23);
				ZVAL_LONG(&_39$$23, 3);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_39$$23, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "longtext")) {
				ZEPHIR_INIT_NVAR(&_40$$24);
				ZVAL_LONG(&_40$$24, 24);
				zephir_array_update_zval(&fieldTypes, &columnName, &_40$$24, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_41$$24);
				ZVAL_LONG(&_41$$24, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_41$$24, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "mediumblob")) {
				ZEPHIR_INIT_NVAR(&_42$$25);
				ZVAL_LONG(&_42$$25, 12);
				zephir_array_update_zval(&fieldTypes, &columnName, &_42$$25, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_43$$25);
				ZVAL_LONG(&_43$$25, 3);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_43$$25, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "mediumint")) {
				ZEPHIR_INIT_NVAR(&_44$$26);
				ZVAL_LONG(&_44$$26, 21);
				zephir_array_update_zval(&fieldTypes, &columnName, &_44$$26, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_45$$26);
				ZVAL_LONG(&_45$$26, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_45$$26, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "mediumtext")) {
				ZEPHIR_INIT_NVAR(&_46$$27);
				ZVAL_LONG(&_46$$27, 23);
				zephir_array_update_zval(&fieldTypes, &columnName, &_46$$27, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_47$$27);
				ZVAL_LONG(&_47$$27, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_47$$27, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "smallint")) {
				ZEPHIR_INIT_NVAR(&_48$$28);
				ZVAL_LONG(&_48$$28, 22);
				zephir_array_update_zval(&fieldTypes, &columnName, &_48$$28, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_49$$28);
				ZVAL_LONG(&_49$$28, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_49$$28, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "text")) {
				ZEPHIR_INIT_NVAR(&_50$$29);
				ZVAL_LONG(&_50$$29, 6);
				zephir_array_update_zval(&fieldTypes, &columnName, &_50$$29, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_51$$29);
				ZVAL_LONG(&_51$$29, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_51$$29, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "time")) {
				ZEPHIR_INIT_NVAR(&_52$$30);
				ZVAL_LONG(&_52$$30, 20);
				zephir_array_update_zval(&fieldTypes, &columnName, &_52$$30, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_53$$30);
				ZVAL_LONG(&_53$$30, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_53$$30, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "timestamp")) {
				ZEPHIR_INIT_NVAR(&_54$$31);
				ZVAL_LONG(&_54$$31, 17);
				zephir_array_update_zval(&fieldTypes, &columnName, &_54$$31, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_55$$31);
				ZVAL_LONG(&_55$$31, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_55$$31, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "tinyblob")) {
				ZEPHIR_INIT_NVAR(&_56$$32);
				ZVAL_LONG(&_56$$32, 10);
				zephir_array_update_zval(&fieldTypes, &columnName, &_56$$32, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_57$$32);
				ZVAL_LONG(&_57$$32, 3);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_57$$32, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "tinyint")) {
				ZEPHIR_INIT_NVAR(&_58$$33);
				ZVAL_LONG(&_58$$33, 26);
				zephir_array_update_zval(&fieldTypes, &columnName, &_58$$33, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_59$$33);
				ZVAL_LONG(&_59$$33, 1);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_59$$33, PH_COPY | PH_SEPARATE);
				zephir_array_update_zval(&numericTyped, &columnName, &__$true, PH_COPY | PH_SEPARATE);
				break;
			}
			if (ZEPHIR_IS_STRING(&feature, "tinytext")) {
				ZEPHIR_INIT_NVAR(&_60$$34);
				ZVAL_LONG(&_60$$34, 25);
				zephir_array_update_zval(&fieldTypes, &columnName, &_60$$34, PH_COPY | PH_SEPARATE);
				ZEPHIR_INIT_NVAR(&_61$$34);
				ZVAL_LONG(&_61$$34, 2);
				zephir_array_update_zval(&fieldBindTypes, &columnName, &_61$$34, PH_COPY | PH_SEPARATE);
				break;
			}
			ZEPHIR_INIT_NVAR(&_62$$35);
			ZVAL_LONG(&_62$$35, 2);
			zephir_array_update_zval(&fieldTypes, &columnName, &_62$$35, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(&_63$$35);
			ZVAL_LONG(&_63$$35, 2);
			zephir_array_update_zval(&fieldBindTypes, &columnName, &_63$$35, PH_COPY | PH_SEPARATE);
		} while(0);

		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Primary");
		ZEPHIR_CALL_METHOD(&_64$$6, &propAnnotations, "has", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_64$$6)) {
			zephir_array_append(&primaryKeys, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 337);
		} else {
			zephir_array_append(&nonPrimaryKeys, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 339);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "Identity");
		ZEPHIR_CALL_METHOD(&_65$$6, &propAnnotations, "has", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_65$$6)) {
			ZEPHIR_CPY_WRT(&identityField, &columnName);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "skip_on_insert");
		ZEPHIR_CALL_METHOD(&_66$$6, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_66$$6)) {
			zephir_array_append(&skipOnInsert, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 354);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "skip_on_update");
		ZEPHIR_CALL_METHOD(&_67$$6, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_67$$6)) {
			zephir_array_append(&skipOnUpdate, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 361);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "allow_empty_string");
		ZEPHIR_CALL_METHOD(&_68$$6, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (zephir_is_true(&_68$$6)) {
			zephir_array_append(&emptyStringValues, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 368);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "nullable");
		ZEPHIR_CALL_METHOD(&_69$$6, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		if (!(zephir_is_true(&_69$$6))) {
			zephir_array_append(&notNull, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 375);
		}
		ZEPHIR_INIT_NVAR(&_9$$6);
		ZVAL_STRING(&_9$$6, "default");
		ZEPHIR_CALL_METHOD(&defaultValue, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
		zephir_check_call_status();
		_70$$6 = Z_TYPE_P(&defaultValue) != IS_NULL;
		if (!(_70$$6)) {
			ZEPHIR_INIT_NVAR(&_9$$6);
			ZVAL_STRING(&_9$$6, "nullable");
			ZEPHIR_CALL_METHOD(&_71$$6, &columnAnnotation, "getnamedparameter", NULL, 0, &_9$$6);
			zephir_check_call_status();
			_70$$6 = zephir_is_true(&_71$$6);
		}
		if (_70$$6) {
			zephir_array_update_zval(&defaultValues, &columnName, &defaultValue, PH_COPY | PH_SEPARATE);
		}
		zephir_array_append(&attributes, &columnName, PH_SEPARATE, "phalcon/Mvc/Model/MetaData/Strategy/Annotations.zep", 387);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&propAnnotations);
	ZEPHIR_INIT_NVAR(&property);
	zephir_create_array(return_value, 12, 0 TSRMLS_CC);
	zephir_array_update_long(return_value, 0, &attributes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 1, &primaryKeys, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 2, &nonPrimaryKeys, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 3, &notNull, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 4, &fieldTypes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 5, &numericTyped, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 8, &identityField, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 9, &fieldBindTypes, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 10, &skipOnInsert, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 11, &skipOnUpdate, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 12, &defaultValues, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_array_update_long(return_value, 13, &emptyStringValues, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	RETURN_MM();

}


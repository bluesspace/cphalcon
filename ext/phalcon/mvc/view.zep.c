
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/array.h"
#include "kernel/file.h"
#include "kernel/concat.h"
#include "kernel/string.h"
#include "Zend/zend_closures.h"


/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */
/**
 * Phalcon\Mvc\View
 *
 * Phalcon\Mvc\View is a class for working with the "view" portion of the
 * model-view-controller pattern. That is, it exists to help keep the view
 * script separate from the model and controller scripts. It provides a system
 * of helpers, output filters, and variable escaping.
 *
 * <code>
 * use Phalcon\Mvc\View;
 *
 * $view = new View();
 *
 * // Setting views directory
 * $view->setViewsDir("app/views/");
 *
 * $view->start();
 *
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->render("posts", "recent");
 * $view->finish();
 *
 * // Printing views output
 * echo $view->getContent();
 * </code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Mvc_View) {

	ZEPHIR_REGISTER_CLASS_EX(Phalcon\\Mvc, View, phalcon, mvc_view, phalcon_di_injectable_ce, phalcon_mvc_view_method_entry, 0);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("actionName"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("activeRenderPaths"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_view_ce, SL("basePath"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_view_ce, SL("content"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("controllerName"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_mvc_view_ce, SL("currentRenderLevel"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(phalcon_mvc_view_ce, SL("disabled"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("disabledLevels"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_bool(phalcon_mvc_view_ce, SL("engines"), 0, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("layout"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_view_ce, SL("layoutsDir"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_view_ce, SL("mainView"), "index", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("options"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("params"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("pickView"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_string(phalcon_mvc_view_ce, SL("partialsDir"), "", ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("registeredEngines"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_long(phalcon_mvc_view_ce, SL("renderLevel"), 5, ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesAfter"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("templatesBefore"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewsDirs"), ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(phalcon_mvc_view_ce, SL("viewParams"), ZEND_ACC_PROTECTED TSRMLS_CC);

	phalcon_mvc_view_ce->create_object = zephir_init_properties_Phalcon_Mvc_View;
	/**
	 * Render Level: To the action view
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_ACTION_VIEW"), 1);

	/**
	 * Render Level: To the templates "before"
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_BEFORE_TEMPLATE"), 2);

	/**
	 * Render Level: To the controller layout
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_LAYOUT"), 3);

	/**
	 * Render Level: To the main layout
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_MAIN_LAYOUT"), 5);

	/**
	 * Render Level: No render any view
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_NO_RENDER"), 0);

	/**
	 * Render Level: Render to the templates "after"
	 */
	zephir_declare_class_constant_long(phalcon_mvc_view_ce, SL("LEVEL_AFTER_TEMPLATE"), 4);

	zend_class_implements(phalcon_mvc_view_ce TSRMLS_CC, 1, phalcon_mvc_viewinterface_ce);
	return SUCCESS;

}

PHP_METHOD(Phalcon_Mvc_View, getCurrentRenderLevel) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "currentRenderLevel");

}

PHP_METHOD(Phalcon_Mvc_View, getRegisteredEngines) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "registeredEngines");

}

PHP_METHOD(Phalcon_Mvc_View, getRenderLevel) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "renderLevel");

}

/**
 * Phalcon\Mvc\View constructor
 */
PHP_METHOD(Phalcon_Mvc_View, __construct) {

	zval *options_param = NULL;
	zval options;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&options);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &options_param);

	if (!options_param) {
		ZEPHIR_INIT_VAR(&options);
		array_init(&options);
	} else {
		zephir_get_arrval(&options, options_param);
	}


	zephir_update_property_zval(this_ptr, SL("options"), &options);
	ZEPHIR_MM_RESTORE();

}

/**
 * Magic method to retrieve a variable passed to the view
 *
 *<code>
 * echo $this->view->products;
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, __get) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getvar", NULL, 0, &key);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Magic method to retrieve if a variable is set in the view
 *
 *<code>
 * echo isset($this->view->products);
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, __isset) {

	zval *key_param = NULL, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	zephir_read_property(&_0, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
	RETURN_MM_BOOL(zephir_array_isset(&_0, &key));

}

/**
 * Magic method to pass variables to the views
 *
 *<code>
 * $this->view->products = $products;
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, __set) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvar", NULL, 0, &key, value);
	zephir_check_call_status();
	ZEPHIR_MM_RESTORE();

}

/**
 * Resets any template before layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateAfter) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("templatesAfter"), &_0);
	RETURN_THIS();

}

/**
 * Resets any "template before" layouts
 */
PHP_METHOD(Phalcon_Mvc_View, cleanTemplateBefore) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	array_init(&_0);
	zephir_update_property_zval(this_ptr, SL("templatesBefore"), &_0);
	RETURN_THIS();

}

/**
 * Disables a specific level of rendering
 *
 *<code>
 * // Render all levels except ACTION level
 * $this->view->disableLevel(
 *     View::LEVEL_ACTION_VIEW
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, disableLevel) {

	zval *level, level_sub, __$true;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&level_sub);
	ZVAL_BOOL(&__$true, 1);

	zephir_fetch_params(0, 1, 0, &level);



	if (Z_TYPE_P(level) == IS_ARRAY) {
		zephir_update_property_zval(this_ptr, SL("disabledLevels"), level);
	} else {
		zephir_update_property_array(this_ptr, SL("disabledLevels"), level, &__$true TSRMLS_CC);
	}
	RETURN_THISW();

}

/**
 * Disables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, disable) {

	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);


	if (1) {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$false);
	}
	RETURN_THISW();

}

/**
 * Enables the auto-rendering process
 */
PHP_METHOD(Phalcon_Mvc_View, enable) {

	zval __$true, __$false;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);


	if (0) {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$false);
	}
	RETURN_THISW();

}

/**
 * Checks whether view exists
 */
PHP_METHOD(Phalcon_Mvc_View, exists) {

	zend_string *_6$$4;
	zend_ulong _5$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *view_param = NULL, basePath, viewsDir, engines, extension, _0, _1, *_2, _3$$4, *_4$$4, _7$$5;
	zval view;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &view_param);

	if (UNEXPECTED(Z_TYPE_P(view_param) != IS_STRING && Z_TYPE_P(view_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'view' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(view_param) == IS_STRING)) {
		zephir_get_strval(&view, view_param);
	} else {
		ZEPHIR_INIT_VAR(&view);
		ZVAL_EMPTY_STRING(&view);
	}


	zephir_read_property(&_0, this_ptr, SL("basePath"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	ZEPHIR_OBS_VAR(&engines);
	zephir_read_property(&engines, this_ptr, SL("registeredEngines"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(&engines)) {
		ZEPHIR_INIT_NVAR(&engines);
		zephir_create_array(&engines, 1, 0 TSRMLS_CC);
		add_assoc_stringl_ex(&engines, SL(".phtml"), SL("Phalcon\\Mvc\\View\\Engine\\Php"));
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "registerengines", NULL, 0, &engines);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "phalcon/Mvc/View.zep", 234);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&viewsDir);
		ZVAL_COPY(&viewsDir, _2);
		ZEPHIR_INIT_NVAR(&_3$$4);
		zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 232);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _5$$4, _6$$4, _4$$4)
		{
			ZEPHIR_INIT_NVAR(&extension);
			if (_6$$4 != NULL) { 
				ZVAL_STR_COPY(&extension, _6$$4);
			} else {
				ZVAL_LONG(&extension, _5$$4);
			}
			ZEPHIR_INIT_NVAR(&_3$$4);
			ZVAL_COPY(&_3$$4, _4$$4);
			ZEPHIR_INIT_LNVAR(_7$$5);
			ZEPHIR_CONCAT_VVVV(&_7$$5, &basePath, &viewsDir, &view, &extension);
			if ((zephir_file_exists(&_7$$5 TSRMLS_CC) == SUCCESS)) {
				RETURN_MM_BOOL(1);
			}
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&_3$$4);
		ZEPHIR_INIT_NVAR(&extension);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&viewsDir);
	RETURN_MM_BOOL(0);

}

/**
 * Finishes the render process by stopping the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, finish) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(NULL, "ob_end_clean", NULL, 175);
	zephir_check_call_status();
	RETURN_THIS();

}

/**
 * Gets the name of the action rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActionName) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "actionName");

}

/**
 * Returns the path (or paths) of the views that are currently rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getActiveRenderPath) {

	zend_bool _1$$3;
	zval activeRenderPath, _0, _2$$4;
	zend_long ZEPHIR_LAST_CALL_STATUS, viewsDirsCount = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&activeRenderPath);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	viewsDirsCount = zephir_fast_count_int(&_0 TSRMLS_CC);
	ZEPHIR_OBS_VAR(&activeRenderPath);
	zephir_read_property(&activeRenderPath, this_ptr, SL("activeRenderPaths"), PH_NOISY_CC);
	if (viewsDirsCount == 1) {
		_1$$3 = Z_TYPE_P(&activeRenderPath) == IS_ARRAY;
		if (_1$$3) {
			_1$$3 = ((zephir_fast_count_int(&activeRenderPath TSRMLS_CC)) ? 1 : 0);
		}
		if (_1$$3) {
			zephir_array_fetch_long(&_2$$4, &activeRenderPath, 0, PH_NOISY | PH_READONLY, "phalcon/Mvc/View.zep", 268 TSRMLS_CC);
			ZEPHIR_CPY_WRT(&activeRenderPath, &_2$$4);
		}
	}
	if (Z_TYPE_P(&activeRenderPath) == IS_NULL) {
		ZEPHIR_INIT_NVAR(&activeRenderPath);
		ZVAL_STRING(&activeRenderPath, "");
	}
	RETURN_CCTOR(&activeRenderPath);

}

/**
 * Gets base path
 */
PHP_METHOD(Phalcon_Mvc_View, getBasePath) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "basePath");

}

/**
 * Returns output from another view stage
 */
PHP_METHOD(Phalcon_Mvc_View, getContent) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "content");

}

/**
 * Gets the name of the controller rendered
 */
PHP_METHOD(Phalcon_Mvc_View, getControllerName) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "controllerName");

}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getLayout) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "layout");

}

/**
 * Gets the current layouts sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getLayoutsDir) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "layoutsDir");

}

/**
 * Returns the name of the main view
 */
PHP_METHOD(Phalcon_Mvc_View, getMainView) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "mainView");

}

/**
 * Returns parameters to views
 */
PHP_METHOD(Phalcon_Mvc_View, getParamsToView) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "viewParams");

}

/**
 * Renders a partial view
 *
 * <code>
 * // Retrieve the contents of a partial
 * echo $this->getPartial("shared/footer");
 * </code>
 *
 * <code>
 * // Retrieve the contents of a partial with arguments
 * echo $this->getPartial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, getPartial) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *partialPath_param = NULL, *params = NULL, params_sub, __$null;
	zval partialPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &partialPath_param, &params);

	if (UNEXPECTED(Z_TYPE_P(partialPath_param) != IS_STRING && Z_TYPE_P(partialPath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'partialPath' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(partialPath_param) == IS_STRING)) {
		zephir_get_strval(&partialPath, partialPath_param);
	} else {
		ZEPHIR_INIT_VAR(&partialPath);
		ZVAL_EMPTY_STRING(&partialPath);
	}
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}


	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 371);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "partial", NULL, 0, &partialPath, params);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_FUNCTION("ob_get_clean", NULL, 378);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Gets the current partials sub-directory
 */
PHP_METHOD(Phalcon_Mvc_View, getPartialsDir) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "partialsDir");

}

/**
 * Perform the automatic rendering returning the output as a string
 *
 * <code>
 * $template = $this->view->getRender(
 *     "products",
 *     "show",
 *     [
 *         "products" => $products,
 *     ]
 * );
 * </code>
 *
 * @param mixed configCallback
 */
PHP_METHOD(Phalcon_Mvc_View, getRender) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params, _1$$4;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, *configCallback = NULL, configCallback_sub, __$null, view, _0$$4;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&configCallback_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&view);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_1$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &controllerName_param, &actionName_param, &params_param, &configCallback);

	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
		ZVAL_EMPTY_STRING(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
		ZVAL_EMPTY_STRING(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!configCallback) {
		configCallback = &configCallback_sub;
		configCallback = &__$null;
	}


	ZEPHIR_INIT_VAR(&view);
	if (zephir_clone(&view, this_ptr TSRMLS_CC) == FAILURE) {
		RETURN_MM();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "reset", NULL, 0);
	zephir_check_call_status();
	if (1 == 1) {
		ZEPHIR_CALL_METHOD(NULL, &view, "setvars", NULL, 0, &params);
		zephir_check_call_status();
	}
	if (Z_TYPE_P(configCallback) == IS_OBJECT) {
		ZEPHIR_INIT_VAR(&_0$$4);
		ZEPHIR_INIT_VAR(&_1$$4);
		zephir_create_array(&_1$$4, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_1$$4, &view);
		ZEPHIR_CALL_USER_FUNC_ARRAY(&_0$$4, configCallback, &_1$$4);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(NULL, &view, "start", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, &view, "render", NULL, 0, &controllerName, &actionName);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(NULL, "ob_end_clean", NULL, 175);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&view, "getcontent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Returns a parameter previously set in the view
 */
PHP_METHOD(Phalcon_Mvc_View, getVar) {

	zval *key_param = NULL, value, _0;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &key_param);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	zephir_read_property(&_0, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset_fetch(&value, &_0, &key, 1 TSRMLS_CC))) {
		RETURN_MM_NULL();
	}
	RETURN_CTOR(&value);

}

/**
 * Gets views directory
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDir) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "viewsDirs");

}

/**
 * Gets views directories
 */
PHP_METHOD(Phalcon_Mvc_View, getViewsDirs) {

	zval _0, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("viewsDirs"), PH_NOISY_CC);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		zephir_create_array(return_value, 1, 0 TSRMLS_CC);
		ZEPHIR_OBS_VAR(&_1$$3);
		zephir_read_property(&_1$$3, this_ptr, SL("viewsDirs"), PH_NOISY_CC);
		zephir_array_fast_append(return_value, &_1$$3);
		RETURN_MM();
	}
	RETURN_MM_MEMBER(getThis(), "viewsDirs");

}

/**
 * Whether automatic rendering is enabled
 */
PHP_METHOD(Phalcon_Mvc_View, isDisabled) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "disabled");

}

/**
 * Renders a partial view
 *
 * <code>
 * // Show a partial inside another view
 * $this->partial("shared/footer");
 * </code>
 *
 * <code>
 * // Show a partial inside another view with parameters
 * $this->partial(
 *     "shared/footer",
 *     [
 *         "content" => $html,
 *     ]
 * );
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, partial) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *partialPath_param = NULL, *params = NULL, params_sub, __$null, viewParams, _3, _4, _5, _6, _7, _0$$3, _1$$3, _2$$3;
	zval partialPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialPath);
	ZVAL_UNDEF(&params_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &partialPath_param, &params);

	if (UNEXPECTED(Z_TYPE_P(partialPath_param) != IS_STRING && Z_TYPE_P(partialPath_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'partialPath' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(partialPath_param) == IS_STRING)) {
		zephir_get_strval(&partialPath, partialPath_param);
	} else {
		ZEPHIR_INIT_VAR(&partialPath);
		ZVAL_EMPTY_STRING(&partialPath);
	}
	if (!params) {
		params = &params_sub;
		params = &__$null;
	}


	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_read_property(&_0$$3, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&viewParams, &_0$$3);
		ZEPHIR_INIT_VAR(&_1$$3);
		zephir_fast_array_merge(&_1$$3, &viewParams, params TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("viewParams"), &_1$$3);
		ZEPHIR_INIT_VAR(&_2$$3);
		zephir_create_symbol_table(TSRMLS_C);
		
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "loadtemplateengines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("partialsDir"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_VV(&_5, &_4, &partialPath);
	ZVAL_BOOL(&_6, 0);
	ZVAL_BOOL(&_7, 0);
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &_3, &_5, &_6, &_7);
	zephir_check_call_status();
	if (Z_TYPE_P(params) == IS_ARRAY) {
		zephir_update_property_zval(this_ptr, SL("viewParams"), &viewParams);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Choose a different view to render instead of last-controller/last-action
 *
 * <code>
 * use Phalcon\Mvc\Controller;
 *
 * class ProductsController extends Controller
 * {
 *    public function saveAction()
 *    {
 *         // Do some save stuff...
 *
 *         // Then show the list view
 *         $this->view->pick("products/list");
 *    }
 * }
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, pick) {

	zval *renderView, renderView_sub, pickView, layout, parts;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&renderView_sub);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&parts);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &renderView);



	if (Z_TYPE_P(renderView) == IS_ARRAY) {
		ZEPHIR_CPY_WRT(&pickView, renderView);
	} else {
		ZEPHIR_INIT_VAR(&layout);
		ZVAL_NULL(&layout);
		if (zephir_memnstr_str(renderView, SL("/"), "phalcon/Mvc/View.zep", 569)) {
			ZEPHIR_INIT_VAR(&parts);
			zephir_fast_explode_str(&parts, SL("/"), renderView, LONG_MAX TSRMLS_CC);
			ZEPHIR_OBS_NVAR(&layout);
			zephir_array_fetch_long(&layout, &parts, 0, PH_NOISY, "phalcon/Mvc/View.zep", 571 TSRMLS_CC);
		}
		ZEPHIR_INIT_NVAR(&pickView);
		zephir_create_array(&pickView, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&pickView, renderView);
		if (Z_TYPE_P(&layout) != IS_NULL) {
			zephir_array_append(&pickView, &layout, PH_SEPARATE, "phalcon/Mvc/View.zep", 577);
		}
	}
	zephir_update_property_zval(this_ptr, SL("pickView"), &pickView);
	RETURN_THIS();

}

/**
 * Register templating engines
 *
 * <code>
 * $this->view->registerEngines(
 *     [
 *         ".phtml" => \Phalcon\Mvc\View\Engine\Php::class,
 *         ".volt"  => \Phalcon\Mvc\View\Engine\Volt::class,
 *         ".mhtml" => \MyCustomEngine::class,
 *     ]
 * );
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, registerEngines) {

	zval *engines_param = NULL;
	zval engines;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &engines_param);

	ZEPHIR_OBS_COPY_OR_DUP(&engines, engines_param);


	zephir_update_property_zval(this_ptr, SL("registeredEngines"), &engines);
	RETURN_THIS();

}

/**
 * Executes render process from dispatching data
 *
 *<code>
 * // Shows recent posts view (app/views/posts/recent.phtml)
 * $view->start()->render("posts", "recent")->finish();
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, render) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, result;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &controllerName_param, &actionName_param, &params_param);

	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
		ZVAL_EMPTY_STRING(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
		ZVAL_EMPTY_STRING(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	ZEPHIR_CALL_METHOD(&result, this_ptr, "processrender", NULL, 0, &controllerName, &actionName, &params);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_BOOL(0);
	}
	RETURN_THIS();

}

/**
 * Resets the view component to its factory default values
 */
PHP_METHOD(Phalcon_Mvc_View, reset) {

	zval __$true, __$false, __$null, _0, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_BOOL(&__$true, 1);
	ZVAL_BOOL(&__$false, 0);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	if (0) {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("disabled"), &__$false);
	}
	if (0) {
		zephir_update_property_zval(this_ptr, SL("engines"), &__$true);
	} else {
		zephir_update_property_zval(this_ptr, SL("engines"), &__$false);
	}
	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, 5);
	zephir_update_property_zval(this_ptr, SL("renderLevel"), &_0);
	zephir_update_property_zval(this_ptr, SL("content"), &__$null);
	ZEPHIR_INIT_VAR(&_1);
	array_init(&_1);
	zephir_update_property_zval(this_ptr, SL("templatesBefore"), &_1);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	zephir_update_property_zval(this_ptr, SL("templatesAfter"), &_2);
	RETURN_THIS();

}

/**
 * Sets base path. Depending of your platform, always add a trailing slash
 * or backslash
 *
 * <code>
 * $view->setBasePath(__DIR__ . "/");
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, setBasePath) {

	zval *basePath_param = NULL;
	zval basePath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&basePath);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &basePath_param);

	zephir_get_strval(&basePath, basePath_param);


	zephir_update_property_zval(this_ptr, SL("basePath"), &basePath);
	RETURN_THIS();

}

/**
 * Externally sets the view content
 *
 *<code>
 * $this->view->setContent("<h1>hello</h1>");
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setContent) {

	zval *content_param = NULL;
	zval content;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&content);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &content_param);

	zephir_get_strval(&content, content_param);


	zephir_update_property_zval(this_ptr, SL("content"), &content);
	RETURN_THIS();

}

/**
 * Change the layout to be used instead of using the name of the latest
 * controller name
 *
 * <code>
 * $this->view->setLayout("main");
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, setLayout) {

	zval *layout_param = NULL;
	zval layout;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layout);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &layout_param);

	zephir_get_strval(&layout, layout_param);


	zephir_update_property_zval(this_ptr, SL("layout"), &layout);
	RETURN_THIS();

}

/**
 * Sets the layouts sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *<code>
 * $view->setLayoutsDir("../common/layouts/");
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setLayoutsDir) {

	zval *layoutsDir_param = NULL;
	zval layoutsDir;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&layoutsDir);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &layoutsDir_param);

	zephir_get_strval(&layoutsDir, layoutsDir_param);


	zephir_update_property_zval(this_ptr, SL("layoutsDir"), &layoutsDir);
	RETURN_THIS();

}

/**
 * Sets default view name. Must be a file without extension in the views
 * directory
 *
 * <code>
 * // Renders as main view views-dir/base.phtml
 * $this->view->setMainView("base");
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, setMainView) {

	zval *viewPath_param = NULL;
	zval viewPath;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewPath);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &viewPath_param);

	zephir_get_strval(&viewPath, viewPath_param);


	zephir_update_property_zval(this_ptr, SL("mainView"), &viewPath);
	RETURN_THIS();

}

/**
 * Sets a partials sub-directory. Must be a directory under the views
 * directory. Depending of your platform, always add a trailing slash or
 * backslash
 *
 *<code>
 * $view->setPartialsDir("../common/partials/");
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setPartialsDir) {

	zval *partialsDir_param = NULL;
	zval partialsDir;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&partialsDir);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &partialsDir_param);

	zephir_get_strval(&partialsDir, partialsDir_param);


	zephir_update_property_zval(this_ptr, SL("partialsDir"), &partialsDir);
	RETURN_THIS();

}

/**
 * Adds parameters to views (alias of setVar)
 *
 *<code>
 * $this->view->setParamToView("products", $products);
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setParamToView) {

	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	zephir_update_property_array(this_ptr, SL("viewParams"), &key, value TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Sets the render level for the view
 *
 * <code>
 * // Render the view related to the controller only
 * $this->view->setRenderLevel(
 *     View::LEVEL_LAYOUT
 * );
 * </code>
 */
PHP_METHOD(Phalcon_Mvc_View, setRenderLevel) {

	zval *level_param = NULL, _0;
	zend_long level;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	zephir_fetch_params(0, 1, 0, &level_param);

	level = zephir_get_intval(level_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, level);
	zephir_update_property_zval(this_ptr, SL("renderLevel"), &_0);
	RETURN_THISW();

}

/**
 * Sets a "template after" controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateAfter) {

	zval _0$$3;
	zval *templateAfter, templateAfter_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateAfter_sub);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &templateAfter);



	if (Z_TYPE_P(templateAfter) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_0$$3, templateAfter);
		zephir_update_property_zval(this_ptr, SL("templatesAfter"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, SL("templatesAfter"), templateAfter);
	}
	RETURN_THIS();

}

/**
 * Sets a template before the controller layout
 */
PHP_METHOD(Phalcon_Mvc_View, setTemplateBefore) {

	zval _0$$3;
	zval *templateBefore, templateBefore_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&templateBefore_sub);
	ZVAL_UNDEF(&_0$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &templateBefore);



	if (Z_TYPE_P(templateBefore) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_create_array(&_0$$3, 1, 0 TSRMLS_CC);
		zephir_array_fast_append(&_0$$3, templateBefore);
		zephir_update_property_zval(this_ptr, SL("templatesBefore"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, SL("templatesBefore"), templateBefore);
	}
	RETURN_THIS();

}

/**
 * Set a single view parameter
 *
 *<code>
 * $this->view->setVar("products", $products);
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setVar) {

	zval *key_param = NULL, *value, value_sub;
	zval key;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&key);
	ZVAL_UNDEF(&value_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &key_param, &value);

	if (UNEXPECTED(Z_TYPE_P(key_param) != IS_STRING && Z_TYPE_P(key_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'key' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(key_param) == IS_STRING)) {
		zephir_get_strval(&key, key_param);
	} else {
		ZEPHIR_INIT_VAR(&key);
		ZVAL_EMPTY_STRING(&key);
	}


	zephir_update_property_array(this_ptr, SL("viewParams"), &key, value TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Set all the render params
 *
 *<code>
 * $this->view->setVars(
 *     [
 *         "products" => $products,
 *     ]
 * );
 *</code>
 */
PHP_METHOD(Phalcon_Mvc_View, setVars) {

	zend_bool merge;
	zval *params_param = NULL, *merge_param = NULL, _0$$3, _1$$3;
	zval params;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&params);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &params_param, &merge_param);

	ZEPHIR_OBS_COPY_OR_DUP(&params, params_param);
	if (!merge_param) {
		merge = 1;
	} else {
		merge = zephir_get_boolval(merge_param);
	}


	if (merge) {
		ZEPHIR_INIT_VAR(&_0$$3);
		zephir_read_property(&_1$$3, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
		zephir_fast_array_merge(&_0$$3, &_1$$3, &params TSRMLS_CC);
		zephir_update_property_zval(this_ptr, SL("viewParams"), &_0$$3);
	} else {
		zephir_update_property_zval(this_ptr, SL("viewParams"), &params);
	}
	RETURN_THIS();

}

/**
 * Sets the views directory. Depending of your platform,
 * always add a trailing slash or backslash
 */
PHP_METHOD(Phalcon_Mvc_View, setViewsDir) {

	zend_string *_5$$5;
	zend_ulong _4$$5;
	zend_bool _0;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_2 = NULL;
	zval *viewsDir, viewsDir_sub, position, directory, newViewsDir, _1$$4, *_3$$5, _6$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&viewsDir_sub);
	ZVAL_UNDEF(&position);
	ZVAL_UNDEF(&directory);
	ZVAL_UNDEF(&newViewsDir);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_6$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &viewsDir);



	_0 = Z_TYPE_P(viewsDir) != IS_STRING;
	if (_0) {
		_0 = Z_TYPE_P(viewsDir) != IS_ARRAY;
	}
	if (_0) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory must be a string or an array", "phalcon/Mvc/View.zep", 842);
		return;
	}
	if (Z_TYPE_P(viewsDir) == IS_STRING) {
		ZEPHIR_CALL_CE_STATIC(&_1$$4, phalcon_helper_str_ce, "dirseparator", &_2, 96, viewsDir);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("viewsDirs"), &_1$$4);
	} else {
		ZEPHIR_INIT_VAR(&newViewsDir);
		array_init(&newViewsDir);
		zephir_is_iterable(viewsDir, 0, "phalcon/Mvc/View.zep", 860);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(viewsDir), _4$$5, _5$$5, _3$$5)
		{
			ZEPHIR_INIT_NVAR(&position);
			if (_5$$5 != NULL) { 
				ZVAL_STR_COPY(&position, _5$$5);
			} else {
				ZVAL_LONG(&position, _4$$5);
			}
			ZEPHIR_INIT_NVAR(&directory);
			ZVAL_COPY(&directory, _3$$5);
			if (Z_TYPE_P(&directory) != IS_STRING) {
				ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_mvc_view_exception_ce, "Views directory item must be a string", "phalcon/Mvc/View.zep", 854);
				return;
			}
			ZEPHIR_CALL_CE_STATIC(&_6$$6, phalcon_helper_str_ce, "dirseparator", &_2, 96, &directory);
			zephir_check_call_status();
			zephir_array_update_zval(&newViewsDir, &position, &_6$$6, PH_COPY | PH_SEPARATE);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&directory);
		ZEPHIR_INIT_NVAR(&position);
		zephir_update_property_zval(this_ptr, SL("viewsDirs"), &newViewsDir);
	}
	RETURN_THIS();

}

/**
 * Starts rendering process enabling the output buffering
 */
PHP_METHOD(Phalcon_Mvc_View, start) {

	zval __$null;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_NULL(&__$null);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_FUNCTION(NULL, "ob_start", NULL, 371);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("content"), &__$null);
	RETURN_THIS();

}

/**
 * Renders the view and returns it as a string
 */
PHP_METHOD(Phalcon_Mvc_View, toString) {

	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, result, _0;
	zval controllerName, actionName;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &controllerName_param, &actionName_param, &params_param);

	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
		ZVAL_EMPTY_STRING(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
		ZVAL_EMPTY_STRING(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}


	ZEPHIR_CALL_METHOD(NULL, this_ptr, "start", NULL, 0);
	zephir_check_call_status();
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(&result, this_ptr, "processrender", NULL, 0, &controllerName, &actionName, &params, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, this_ptr, "finish", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&result))) {
		RETURN_MM_STRING("");
	}
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "getcontent", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Checks whether view exists on registered extensions and render it
 */
PHP_METHOD(Phalcon_Mvc_View, engineRender) {

	zend_string *_7$$3;
	zend_ulong _6$$3;
	zephir_fcall_cache_entry *_4 = NULL, *_11 = NULL, *_14 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool silence, mustClean, notExists = 0;
	zval viewPath, _17$$13;
	zval *engines_param = NULL, *viewPath_param = NULL, *silence_param = NULL, *mustClean_param = NULL, basePath, engine, eventsManager, extension, viewsDir, viewsDirPath, viewEnginePath, viewEnginePaths, viewParams, _0, _1, *_2, _3$$3, *_5$$3, _9$$8, _10$$8, _12$$7, _13$$10, _15$$12, _16$$13;
	zval engines, _8$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&basePath);
	ZVAL_UNDEF(&engine);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&viewsDir);
	ZVAL_UNDEF(&viewsDirPath);
	ZVAL_UNDEF(&viewEnginePath);
	ZVAL_UNDEF(&viewEnginePaths);
	ZVAL_UNDEF(&viewParams);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_16$$13);
	ZVAL_UNDEF(&viewPath);
	ZVAL_UNDEF(&_17$$13);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 1, &engines_param, &viewPath_param, &silence_param, &mustClean_param);

	zephir_get_arrval(&engines, engines_param);
	zephir_get_strval(&viewPath, viewPath_param);
	silence = zephir_get_boolval(silence_param);
	if (!mustClean_param) {
		mustClean = 1;
	} else {
		mustClean = zephir_get_boolval(mustClean_param);
	}


	notExists = 1;
	zephir_read_property(&_0, this_ptr, SL("basePath"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&basePath, &_0);
	zephir_read_property(&_0, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&viewParams, &_0);
	zephir_read_property(&_0, this_ptr, SL("eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_0);
	ZEPHIR_INIT_VAR(&viewEnginePaths);
	array_init(&viewEnginePaths);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "getviewsdirs", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_1, 0, "phalcon/Mvc/View.zep", 970);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
	{
		ZEPHIR_INIT_NVAR(&viewsDir);
		ZVAL_COPY(&viewsDir, _2);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "isabsolutepath", &_4, 479, &viewPath);
		zephir_check_call_status();
		if (!(zephir_is_true(&_3$$3))) {
			ZEPHIR_INIT_NVAR(&viewsDirPath);
			ZEPHIR_CONCAT_VVV(&viewsDirPath, &basePath, &viewsDir, &viewPath);
		} else {
			ZEPHIR_CPY_WRT(&viewsDirPath, &viewPath);
		}
		zephir_is_iterable(&engines, 0, "phalcon/Mvc/View.zep", 968);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&engines), _6$$3, _7$$3, _5$$3)
		{
			ZEPHIR_INIT_NVAR(&extension);
			if (_7$$3 != NULL) { 
				ZVAL_STR_COPY(&extension, _7$$3);
			} else {
				ZVAL_LONG(&extension, _6$$3);
			}
			ZEPHIR_INIT_NVAR(&engine);
			ZVAL_COPY(&engine, _5$$3);
			ZEPHIR_INIT_NVAR(&viewEnginePath);
			ZEPHIR_CONCAT_VV(&viewEnginePath, &viewsDirPath, &extension);
			if ((zephir_file_exists(&viewEnginePath TSRMLS_CC) == SUCCESS)) {
				if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_8$$8);
					zephir_create_array(&_8$$8, 1, 0 TSRMLS_CC);
					zephir_array_fast_append(&_8$$8, &viewEnginePath);
					zephir_update_property_zval(this_ptr, SL("activeRenderPaths"), &_8$$8);
					ZEPHIR_INIT_NVAR(&_10$$8);
					ZVAL_STRING(&_10$$8, "view:beforeRenderView");
					ZEPHIR_CALL_METHOD(&_9$$8, &eventsManager, "fire", &_11, 0, &_10$$8, this_ptr, &viewEnginePath);
					zephir_check_call_status();
					if (ZEPHIR_IS_FALSE_IDENTICAL(&_9$$8)) {
						continue;
					}
				}
				if (mustClean) {
					ZVAL_BOOL(&_12$$7, 1);
				} else {
					ZVAL_BOOL(&_12$$7, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, &engine, "render", NULL, 0, &viewEnginePath, &viewParams, &_12$$7);
				zephir_check_call_status();
				notExists = 0;
				if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
					ZEPHIR_INIT_NVAR(&_13$$10);
					ZVAL_STRING(&_13$$10, "view:afterRenderView");
					ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", &_14, 0, &_13$$10, this_ptr);
					zephir_check_call_status();
				}
				break;
			}
			zephir_array_append(&viewEnginePaths, &viewEnginePath, PH_SEPARATE, "phalcon/Mvc/View.zep", 966);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&engine);
		ZEPHIR_INIT_NVAR(&extension);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&viewsDir);
	if (notExists) {
		if (Z_TYPE_P(&eventsManager) == IS_OBJECT) {
			zephir_update_property_zval(this_ptr, SL("activeRenderPaths"), &viewEnginePaths);
			ZEPHIR_INIT_VAR(&_15$$12);
			ZVAL_STRING(&_15$$12, "view:notFoundView");
			ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_15$$12, this_ptr, &viewEnginePath);
			zephir_check_call_status();
		}
		if (!(silence)) {
			ZEPHIR_INIT_VAR(&_16$$13);
			object_init_ex(&_16$$13, phalcon_mvc_view_exception_ce);
			ZEPHIR_INIT_VAR(&_17$$13);
			ZEPHIR_CONCAT_SVS(&_17$$13, "View '", &viewPath, "' was not found in any of the views directory");
			ZEPHIR_CALL_METHOD(NULL, &_16$$13, "__construct", NULL, 1, &_17$$13);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_16$$13, "phalcon/Mvc/View.zep", 983 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Checks if a path is absolute or not
 */
PHP_METHOD(Phalcon_Mvc_View, isAbsolutePath) {

	unsigned char _6, _2$$3, _4$$3;
	zend_bool _5, _1$$3, _3$$3;
	zval *path_param = NULL, _0;
	zval path;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&path);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &path_param);

	zephir_get_strval(&path, path_param);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_OS");
	if (ZEPHIR_IS_STRING(&_0, "WINNT")) {
		_1$$3 = zephir_fast_strlen_ev(&path) >= 3;
		if (_1$$3) {
			_2$$3 = ZEPHIR_STRING_OFFSET(&path, 1);
			_1$$3 = _2$$3 == ':';
		}
		_3$$3 = _1$$3;
		if (_3$$3) {
			_4$$3 = ZEPHIR_STRING_OFFSET(&path, 2);
			_3$$3 = _4$$3 == '\\';
		}
		RETURN_MM_BOOL(_3$$3);
	}
	_5 = zephir_fast_strlen_ev(&path) >= 1;
	if (_5) {
		_6 = ZEPHIR_STRING_OFFSET(&path, 0);
		_5 = _6 == '/';
	}
	RETURN_MM_BOOL(_5);

}

/**
 * Loads registered template engines, if none is registered it will use
 * Phalcon\Mvc\View\Engine\Php
 */
PHP_METHOD(Phalcon_Mvc_View, loadTemplateEngines) {

	zval _17$$11;
	zend_class_entry *_11$$9;
	zend_string *_9$$5;
	zend_ulong _8$$5;
	zval engines, di, registeredEngines, engineService, extension, _0, _1$$3, _2$$4, _3$$6, _4$$6, _6$$6, *_7$$5, _10$$9, _14$$12, _15$$12, _16$$11;
	zephir_fcall_cache_entry *_5 = NULL, *_12 = NULL, *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&di);
	ZVAL_UNDEF(&registeredEngines);
	ZVAL_UNDEF(&engineService);
	ZVAL_UNDEF(&extension);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_10$$9);
	ZVAL_UNDEF(&_14$$12);
	ZVAL_UNDEF(&_15$$12);
	ZVAL_UNDEF(&_16$$11);
	ZVAL_UNDEF(&_17$$11);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("engines"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&engines, &_0);
	if (ZEPHIR_IS_FALSE_IDENTICAL(&engines)) {
		zephir_read_property(&_1$$3, this_ptr, SL("container"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&di, &_1$$3);
		ZEPHIR_INIT_NVAR(&engines);
		array_init(&engines);
		zephir_read_property(&_1$$3, this_ptr, SL("registeredEngines"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CPY_WRT(&registeredEngines, &_1$$3);
		if (ZEPHIR_IS_EMPTY(&registeredEngines)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, phalcon_mvc_view_engine_php_ce);
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 480, this_ptr, &di);
			zephir_check_call_status();
			zephir_array_update_string(&engines, SL(".phtml"), &_2$$4, PH_COPY | PH_SEPARATE);
		} else {
			if (Z_TYPE_P(&di) != IS_OBJECT) {
				ZEPHIR_INIT_VAR(&_3$$6);
				object_init_ex(&_3$$6, phalcon_mvc_view_exception_ce);
				ZEPHIR_INIT_VAR(&_6$$6);
				ZVAL_STRING(&_6$$6, "application services");
				ZEPHIR_CALL_CE_STATIC(&_4$$6, phalcon_mvc_view_exception_ce, "containerservicenotfound", &_5, 0, &_6$$6);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 1, &_4$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_3$$6, "phalcon/Mvc/View.zep", 1029 TSRMLS_CC);
				ZEPHIR_MM_RESTORE();
				return;
			}
			zephir_is_iterable(&registeredEngines, 0, "phalcon/Mvc/View.zep", 1066);
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&registeredEngines), _8$$5, _9$$5, _7$$5)
			{
				ZEPHIR_INIT_NVAR(&extension);
				if (_9$$5 != NULL) { 
					ZVAL_STR_COPY(&extension, _9$$5);
				} else {
					ZVAL_LONG(&extension, _8$$5);
				}
				ZEPHIR_INIT_NVAR(&engineService);
				ZVAL_COPY(&engineService, _7$$5);
				if (Z_TYPE_P(&engineService) == IS_OBJECT) {
					if (zephir_instance_of_ev(&engineService, zend_ce_closure TSRMLS_CC)) {
						_11$$9 = zephir_fetch_class_str_ex(SL("Closure"), ZEND_FETCH_CLASS_AUTO);
						ZEPHIR_CALL_CE_STATIC(&_10$$9, _11$$9, "bind", &_12, 0, &engineService, &di);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&engineService, &_10$$9);
						ZEPHIR_CALL_FUNCTION(&_10$$9, "call_user_func", &_13, 225, &engineService, this_ptr);
						zephir_check_call_status();
						zephir_array_update_zval(&engines, &extension, &_10$$9, PH_COPY | PH_SEPARATE);
					} else {
						zephir_array_update_zval(&engines, &extension, &engineService, PH_COPY | PH_SEPARATE);
					}
				} else {
					if (Z_TYPE_P(&engineService) != IS_STRING) {
						ZEPHIR_INIT_NVAR(&_14$$12);
						object_init_ex(&_14$$12, phalcon_mvc_view_exception_ce);
						ZEPHIR_INIT_LNVAR(_15$$12);
						ZEPHIR_CONCAT_SV(&_15$$12, "Invalid template engine registration for extension: ", &extension);
						ZEPHIR_CALL_METHOD(NULL, &_14$$12, "__construct", NULL, 1, &_15$$12);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_14$$12, "phalcon/Mvc/View.zep", 1057 TSRMLS_CC);
						ZEPHIR_MM_RESTORE();
						return;
					}
					ZEPHIR_INIT_NVAR(&_17$$11);
					zephir_create_array(&_17$$11, 1, 0 TSRMLS_CC);
					zephir_array_fast_append(&_17$$11, this_ptr);
					ZEPHIR_CALL_METHOD(&_16$$11, &di, "getshared", NULL, 0, &engineService, &_17$$11);
					zephir_check_call_status();
					zephir_array_update_zval(&engines, &extension, &_16$$11, PH_COPY | PH_SEPARATE);
				}
			} ZEND_HASH_FOREACH_END();
			ZEPHIR_INIT_NVAR(&engineService);
			ZEPHIR_INIT_NVAR(&extension);
		}
		zephir_update_property_zval(this_ptr, SL("engines"), &engines);
	}
	RETURN_CCTOR(&engines);

}

/**
 * Processes the view and templates; Fires events if needed
 */
PHP_METHOD(Phalcon_Mvc_View, processRender) {

	zend_long ZEPHIR_LAST_CALL_STATUS, renderLevel = 0;
	zend_bool fireEvents, silence = 0, _5, _24;
	zval params;
	zval *controllerName_param = NULL, *actionName_param = NULL, *params_param = NULL, *fireEvents_param = NULL, layoutsDir, layout, pickView, layoutName, engines, renderView, pickViewAction, eventsManager, disabledLevels, templatesBefore, templatesAfter, templateBefore, templateAfter, _0, _2, _4, _8, _9, _1$$3, _6$$12, _7$$12, _10$$16, _11$$18, *_12$$18, _13$$19, _14$$19, _15$$21, _16$$21, _17$$23, *_18$$23, _19$$24, _20$$24, _21$$26, _22$$26, _23$$14, _25$$27;
	zval controllerName, actionName, _3$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&controllerName);
	ZVAL_UNDEF(&actionName);
	ZVAL_UNDEF(&_3$$8);
	ZVAL_UNDEF(&layoutsDir);
	ZVAL_UNDEF(&layout);
	ZVAL_UNDEF(&pickView);
	ZVAL_UNDEF(&layoutName);
	ZVAL_UNDEF(&engines);
	ZVAL_UNDEF(&renderView);
	ZVAL_UNDEF(&pickViewAction);
	ZVAL_UNDEF(&eventsManager);
	ZVAL_UNDEF(&disabledLevels);
	ZVAL_UNDEF(&templatesBefore);
	ZVAL_UNDEF(&templatesAfter);
	ZVAL_UNDEF(&templateBefore);
	ZVAL_UNDEF(&templateAfter);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_6$$12);
	ZVAL_UNDEF(&_7$$12);
	ZVAL_UNDEF(&_10$$16);
	ZVAL_UNDEF(&_11$$18);
	ZVAL_UNDEF(&_13$$19);
	ZVAL_UNDEF(&_14$$19);
	ZVAL_UNDEF(&_15$$21);
	ZVAL_UNDEF(&_16$$21);
	ZVAL_UNDEF(&_17$$23);
	ZVAL_UNDEF(&_19$$24);
	ZVAL_UNDEF(&_20$$24);
	ZVAL_UNDEF(&_21$$26);
	ZVAL_UNDEF(&_22$$26);
	ZVAL_UNDEF(&_23$$14);
	ZVAL_UNDEF(&_25$$27);
	ZVAL_UNDEF(&params);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 2, &controllerName_param, &actionName_param, &params_param, &fireEvents_param);

	if (UNEXPECTED(Z_TYPE_P(controllerName_param) != IS_STRING && Z_TYPE_P(controllerName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'controllerName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(controllerName_param) == IS_STRING)) {
		zephir_get_strval(&controllerName, controllerName_param);
	} else {
		ZEPHIR_INIT_VAR(&controllerName);
		ZVAL_EMPTY_STRING(&controllerName);
	}
	if (UNEXPECTED(Z_TYPE_P(actionName_param) != IS_STRING && Z_TYPE_P(actionName_param) != IS_NULL)) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'actionName' must be of the type string") TSRMLS_CC);
		RETURN_MM_NULL();
	}
	if (EXPECTED(Z_TYPE_P(actionName_param) == IS_STRING)) {
		zephir_get_strval(&actionName, actionName_param);
	} else {
		ZEPHIR_INIT_VAR(&actionName);
		ZVAL_EMPTY_STRING(&actionName);
	}
	if (!params_param) {
		ZEPHIR_INIT_VAR(&params);
		array_init(&params);
	} else {
		zephir_get_arrval(&params, params_param);
	}
	if (!fireEvents_param) {
		fireEvents = 1;
	} else {
		fireEvents = zephir_get_boolval(fireEvents_param);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_LONG(&_0, 0);
	zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_0);
	zephir_read_property(&_0, this_ptr, SL("disabled"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_FALSE_IDENTICAL(&_0)) {
		ZEPHIR_CALL_FUNCTION(&_1$$3, "ob_get_contents", NULL, 481);
		zephir_check_call_status();
		zephir_update_property_zval(this_ptr, SL("content"), &_1$$3);
		RETURN_MM_BOOL(0);
	}
	zephir_update_property_zval(this_ptr, SL("controllerName"), &controllerName);
	zephir_update_property_zval(this_ptr, SL("actionName"), &actionName);
	if (1 == 1) {
		ZEPHIR_CALL_METHOD(NULL, this_ptr, "setvars", NULL, 0, &params);
		zephir_check_call_status();
	}
	zephir_read_property(&_2, this_ptr, SL("layoutsDir"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layoutsDir, &_2);
	if (!(zephir_is_true(&layoutsDir))) {
		ZEPHIR_INIT_NVAR(&layoutsDir);
		ZVAL_STRING(&layoutsDir, "layouts/");
	}
	zephir_read_property(&_2, this_ptr, SL("layout"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&layout, &_2);
	if (zephir_is_true(&layout)) {
		ZEPHIR_CPY_WRT(&layoutName, &layout);
	} else {
		ZEPHIR_CPY_WRT(&layoutName, &controllerName);
	}
	ZEPHIR_CALL_METHOD(&engines, this_ptr, "loadtemplateengines", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("pickView"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&pickView, &_2);
	if (Z_TYPE_P(&pickView) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_3$$8);
		ZEPHIR_CONCAT_VSV(&_3$$8, &controllerName, "/", &actionName);
		ZEPHIR_CPY_WRT(&renderView, &_3$$8);
	} else {
		ZEPHIR_OBS_NVAR(&renderView);
		zephir_array_fetch_long(&renderView, &pickView, 0, PH_NOISY, "phalcon/Mvc/View.zep", 1146 TSRMLS_CC);
		if (Z_TYPE_P(&layoutName) == IS_NULL) {
			ZEPHIR_OBS_VAR(&pickViewAction);
			if (zephir_array_isset_long_fetch(&pickViewAction, &pickView, 1, 0 TSRMLS_CC)) {
				ZEPHIR_CPY_WRT(&layoutName, &pickViewAction);
			}
		}
	}
	zephir_read_property(&_2, this_ptr, SL("eventsManager"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&eventsManager, &_2);
	ZEPHIR_INIT_VAR(&_4);
	zephir_create_symbol_table(TSRMLS_C);
	
	_5 = fireEvents;
	if (_5) {
		_5 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_7$$12);
		ZVAL_STRING(&_7$$12, "view:beforeRender");
		ZEPHIR_CALL_METHOD(&_6$$12, &eventsManager, "fire", NULL, 0, &_7$$12, this_ptr);
		zephir_check_call_status();
		if (ZEPHIR_IS_FALSE_IDENTICAL(&_6$$12)) {
			RETURN_MM_BOOL(0);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_8, "ob_get_contents", NULL, 481);
	zephir_check_call_status();
	zephir_update_property_zval(this_ptr, SL("content"), &_8);
	silence = 1;
	zephir_read_property(&_2, this_ptr, SL("disabledLevels"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&disabledLevels, &_2);
	ZEPHIR_OBS_VAR(&_9);
	zephir_read_property(&_9, this_ptr, SL("renderLevel"), PH_NOISY_CC);
	renderLevel = zephir_get_intval(&_9);
	if (renderLevel) {
		if (renderLevel >= 1) {
			if (!(zephir_array_isset_long(&disabledLevels, 1))) {
				ZEPHIR_INIT_ZVAL_NREF(_10$$16);
				ZVAL_LONG(&_10$$16, 1);
				zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_10$$16);
				if (silence) {
					ZVAL_BOOL(&_10$$16, 1);
				} else {
					ZVAL_BOOL(&_10$$16, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &renderView, &_10$$16);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 2) {
			if (!(zephir_array_isset_long(&disabledLevels, 2))) {
				ZEPHIR_INIT_ZVAL_NREF(_11$$18);
				ZVAL_LONG(&_11$$18, 2);
				zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_11$$18);
				zephir_read_property(&_11$$18, this_ptr, SL("templatesBefore"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesBefore, &_11$$18);
				silence = 0;
				zephir_is_iterable(&templatesBefore, 0, "phalcon/Mvc/View.zep", 1222);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&templatesBefore), _12$$18)
				{
					ZEPHIR_INIT_NVAR(&templateBefore);
					ZVAL_COPY(&templateBefore, _12$$18);
					ZEPHIR_INIT_LNVAR(_13$$19);
					ZEPHIR_CONCAT_VV(&_13$$19, &layoutsDir, &templateBefore);
					if (silence) {
						ZVAL_BOOL(&_14$$19, 1);
					} else {
						ZVAL_BOOL(&_14$$19, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_13$$19, &_14$$19);
					zephir_check_call_status();
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&templateBefore);
				silence = 1;
			}
		}
		if (renderLevel >= 3) {
			if (!(zephir_array_isset_long(&disabledLevels, 3))) {
				ZEPHIR_INIT_ZVAL_NREF(_15$$21);
				ZVAL_LONG(&_15$$21, 3);
				zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_15$$21);
				ZEPHIR_INIT_VAR(&_16$$21);
				ZEPHIR_CONCAT_VV(&_16$$21, &layoutsDir, &layoutName);
				if (silence) {
					ZVAL_BOOL(&_15$$21, 1);
				} else {
					ZVAL_BOOL(&_15$$21, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_16$$21, &_15$$21);
				zephir_check_call_status();
			}
		}
		if (renderLevel >= 4) {
			if (!(zephir_array_isset_long(&disabledLevels, 4))) {
				ZEPHIR_INIT_ZVAL_NREF(_17$$23);
				ZVAL_LONG(&_17$$23, 4);
				zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_17$$23);
				zephir_read_property(&_17$$23, this_ptr, SL("templatesAfter"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_CPY_WRT(&templatesAfter, &_17$$23);
				silence = 0;
				zephir_is_iterable(&templatesAfter, 0, "phalcon/Mvc/View.zep", 1258);
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&templatesAfter), _18$$23)
				{
					ZEPHIR_INIT_NVAR(&templateAfter);
					ZVAL_COPY(&templateAfter, _18$$23);
					ZEPHIR_INIT_LNVAR(_19$$24);
					ZEPHIR_CONCAT_VV(&_19$$24, &layoutsDir, &templateAfter);
					if (silence) {
						ZVAL_BOOL(&_20$$24, 1);
					} else {
						ZVAL_BOOL(&_20$$24, 0);
					}
					ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_19$$24, &_20$$24);
					zephir_check_call_status();
				} ZEND_HASH_FOREACH_END();
				ZEPHIR_INIT_NVAR(&templateAfter);
				silence = 1;
			}
		}
		if (renderLevel >= 5) {
			if (!(zephir_array_isset_long(&disabledLevels, 5))) {
				ZEPHIR_INIT_ZVAL_NREF(_21$$26);
				ZVAL_LONG(&_21$$26, 5);
				zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_21$$26);
				zephir_read_property(&_21$$26, this_ptr, SL("mainView"), PH_NOISY_CC | PH_READONLY);
				if (silence) {
					ZVAL_BOOL(&_22$$26, 1);
				} else {
					ZVAL_BOOL(&_22$$26, 0);
				}
				ZEPHIR_CALL_METHOD(NULL, this_ptr, "enginerender", NULL, 0, &engines, &_21$$26, &_22$$26);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_ZVAL_NREF(_23$$14);
		ZVAL_LONG(&_23$$14, 0);
		zephir_update_property_zval(this_ptr, SL("currentRenderLevel"), &_23$$14);
	}
	_24 = fireEvents;
	if (_24) {
		_24 = Z_TYPE_P(&eventsManager) == IS_OBJECT;
	}
	if (_24) {
		ZEPHIR_INIT_VAR(&_25$$27);
		ZVAL_STRING(&_25$$27, "view:afterRender");
		ZEPHIR_CALL_METHOD(NULL, &eventsManager, "fire", NULL, 0, &_25$$27, this_ptr);
		zephir_check_call_status();
	}
	RETURN_MM_BOOL(1);

}

zend_object *zephir_init_properties_Phalcon_Mvc_View(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _2, _4, _6, _8, _10, _1$$3, _3$$4, _5$$5, _7$$6, _9$$7, _11$$8;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_11$$8);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("viewParams"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("viewParams"), &_1$$3);
		}
		zephir_read_property(&_2, this_ptr, SL("viewsDirs"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_2) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_3$$4);
			array_init(&_3$$4);
			zephir_update_property_zval(this_ptr, SL("viewsDirs"), &_3$$4);
		}
		zephir_read_property(&_4, this_ptr, SL("templatesBefore"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_4) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_5$$5);
			array_init(&_5$$5);
			zephir_update_property_zval(this_ptr, SL("templatesBefore"), &_5$$5);
		}
		zephir_read_property(&_6, this_ptr, SL("templatesAfter"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_6) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_7$$6);
			array_init(&_7$$6);
			zephir_update_property_zval(this_ptr, SL("templatesAfter"), &_7$$6);
		}
		zephir_read_property(&_8, this_ptr, SL("registeredEngines"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_8) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_9$$7);
			array_init(&_9$$7);
			zephir_update_property_zval(this_ptr, SL("registeredEngines"), &_9$$7);
		}
		zephir_read_property(&_10, this_ptr, SL("options"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_10) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_11$$8);
			array_init(&_11$$8);
			zephir_update_property_zval(this_ptr, SL("options"), &_11$$8);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}


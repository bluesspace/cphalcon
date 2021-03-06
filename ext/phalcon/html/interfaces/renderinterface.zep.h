
extern zend_class_entry *phalcon_html_interfaces_renderinterface_ce;

ZEPHIR_INIT_CLASS(Phalcon_Html_Interfaces_RenderInterface);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_html_interfaces_renderinterface_render, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_phalcon_html_interfaces_renderinterface_render, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(phalcon_html_interfaces_renderinterface_method_entry) {
	PHP_ABSTRACT_ME(Phalcon_Html_Interfaces_RenderInterface, render, arginfo_phalcon_html_interfaces_renderinterface_render)
	PHP_FE_END
};

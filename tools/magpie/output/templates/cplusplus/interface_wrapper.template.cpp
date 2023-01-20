/* Interface {*-?interface.get_name()-*} */
#if !defined(/*-?interface.get_ifdef_name()-*/)
#define /*-?interface.get_ifdef_name()-*/
typedef CORBA_Object /*-?interface.get_name()-*/;
#endif // !defined(/*-?interface.get_ifdef_name()-*/)
class /*-?interface.get_name()-*/_client {

protected:
	/*-?interface.get_name()-*/ _service;
	CORBA_Environment *_env;

public:
// Class constructor:
/*-?interface.get_name()-*/_client(/*-?interface.get_name()-*/ service, CORBA_Environment *env)
{
	this->_service = service;
	this->_env = env;
}
/*LOOP function = interface.get_functions()*/
/*-run(templates.get('language_specific_remapping'))-*/
/*-run(templates.get('client_function_wrapper'))-*/
/*ENDLOOP*/
};


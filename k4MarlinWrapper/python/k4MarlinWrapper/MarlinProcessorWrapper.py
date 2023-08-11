import Configurables


def propify1 (v):
    if v is True:
        return 'true'
    elif v is False:
        return 'false'
    elif isinstance (v, str):
        return v
    return str(v)

def propify (v):
    if not isinstance (v, list):
        v = [v]
    return [propify1(x) for x in v]


class MarlinProcessorWrapper (Configurables.MarlinProcessorWrapper):
    def __init__ (self, name, type):
        super (Configurables.MarlinProcessorWrapper, self).__init__ (name)
        self.__dict__['ProcessorType'] = type
        self.__dict__['Parameters'] = {}
        return


    def __setattr__ (self, k, v):
        if k == 'OutputLevel' or k.startswith ('_'):
            return super (Configurables.MarlinProcessorWrapper, self).__setattr__ (k, v)
        if k == 'ProcessorType':
            raise NameError ("Cannot alter ProcessorType")

        self.__dict__[k] = v
        self.Parameters[k] = propify (v)
        return

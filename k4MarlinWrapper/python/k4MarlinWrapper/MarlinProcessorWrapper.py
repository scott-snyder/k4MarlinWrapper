import Configurables
import functools


def _propify1 (v):
    if v is True:
        return 'true'
    elif v is False:
        return 'false'
    elif isinstance (v, str):
        return v
    return str(v)

def _propify (v):
    if not isinstance (v, list):
        v = [v]
    return [_propify1(x) for x in v]


class Args:
    def __init__ (self, override = {}, **kw):
        kw.update (override)
        for k, v in kw.items():
            setattr (self, k, v)
        return
    def setParams (self, name, params):
        for k, v in self.__dict__.items():
            params._setParam (name + '.' + k, v)
        return
    def update (self, d):
        for k, v in d.items():
            setattr (self, k, v)
        return


class MarlinProcessorWrapper (Configurables.MarlinProcessorWrapper):
    def __init__ (self, type, name, **kw):
        super (Configurables.MarlinProcessorWrapper, self).__init__ (name)
        self.ProcessorType = type
        self.Parameters = {}
        for k, v in kw.items():
            setattr (self, k, v)
        return


    def __setattr__ (self, k, v):
        if k.startswith ('_') or k in self.properties().keys():
            return super (Configurables.MarlinProcessorWrapper, self).__setattr__ (k, v)

        self.__dict__[k] = v
        self._setParam (k, v)
        return


    def _setParam (self, k, v):
        if isinstance (v, Args):
            v.setParams (k, self)
        else:
            self.Parameters[k] = _propify (v)
        return


def makeProcessorWrapper (type):
    return functools.partial (MarlinProcessorWrapper, type)


for t in ['AIDAProcessor',
          'ConformalTrackingV2',
          'InitializeDD4hep',
          'DDPlanarDigiProcessor',
          'TruthTrackFinder',
          'ClonesAndSplitTracksFinder',
          'ClicEfficiencyCalculator',
          'TrackChecker',
          'Statusmonitor',
          'RefitFinal',
          'DDSimpleMuonDigi',
          'RecoMCTruthLinker',
          'HitResiduals',
          'MarlinLumiCalClusterer',
          'MergeCollections',
          'FastJetProcessor',
          'LcfiplusProcessor',
          'LCIOOutputProcessor',
          'CLICPfoSelector',
          'OverlayTimingGeneric',
          'DDCaloDigi',
          'DDPandoraPFANewProcessor']:
    globals()[t] = makeProcessorWrapper (t)


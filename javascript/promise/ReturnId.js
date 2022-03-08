rnps-prototype-capture-gallery/src/modules/mediaCopy/index.js

function prepareMediaCopyEpic(action$, store) {
  return action$.ofType(PREPARE_MEDIA_COPY)
  .map(action => {
    const { userId } = store.getState().app;
    const { selectList } = store.getState().selectorList;
    const args = selectList.map(appliTitleId => { return { userId, appliTitleId }; });
    return { args };
  })
  .map(action => {
    return action.args.map((arg) => {
      const { appliTitleId } = arg;
      return createAdapter().then(({ ctxId }) => {
        return setSearchCondition(ctxId, arg).then(() => {
          return getItems(ctxId, appliTitleId).then(({ items }) => {
            deleteAdapter(ctxId);
            const { pcl } = store.getState().app;
            return getMrids(items, appliTitleId, pcl);
          })
          .catch(() => deleteAdapter(ctxId));
        })
        .catch(() => deleteAdapter(ctxId));
      });
    });
  })
  .mergeMap(promises => Promise.all(promises)
    .then(createStartMediaCopyAction)
    .catch(() => errorMediaCopy('CAP12'))
  );
}


function createStartMediaCopyAction(results) {
  let copyList = [];
  for (let i = 0; i < results.length; i++) {
    copyList = copyList.concat(results[i]);
  }
  return startMediaCopy(copyList);
}

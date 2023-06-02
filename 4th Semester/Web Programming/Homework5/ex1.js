const moveSelectedFromListToOther = (fromList, toList) => {
    if (fromList.prop('selectedIndex') !== -1) {
        toList.append(fromList.find(':selected'))
            .prop('selectedIndex', -1)
            .prop('size', toList.children().length);
        fromList.prop('size', fromList.children().length);
    }
}

const firstList = $('#firstList');
const secondList = $('#secondList');
firstList.prop('size', firstList.children().length)
    .dblclick(() => moveSelectedFromListToOther(firstList, secondList))
secondList.prop('size', secondList.children().length)
    .dblclick(() => moveSelectedFromListToOther(secondList, firstList));

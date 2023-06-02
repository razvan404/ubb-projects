moveSelectedFromListToOtherFunction = (fromList, toList) => {
    return (ev) => {
        const selItemIdx = fromList.selectedIndex;
        if (selItemIdx === -1 || selItemIdx === 0) {
            return;
        }
        toList.appendChild(fromList[selItemIdx]);
        fromList.selectedIndex = 0;
    }
}
const firstList = document.getElementById("firstList");
const secondList = document.getElementById("secondList");
console.log(firstList);
firstList.ondblclick = moveSelectedFromListToOtherFunction(firstList, secondList);
secondList.ondblclick = moveSelectedFromListToOtherFunction(secondList, firstList);
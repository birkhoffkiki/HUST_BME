
Page({
  data: {
    //控制按钮是否可点击
    btnState: true,
    //用户选择的图片
    imageUserScr: '/pages/image/old_man.gif',

  },

  //生命周期，刚进来
  onLoad: function () {

  },

  again() {
    //控制按钮
    if (this.data.btnState == false) {
      return;
    }
    wx.navigateTo({
      url: '../come_on/come_on',
    })
  }, 


})